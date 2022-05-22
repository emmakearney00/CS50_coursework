import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash


from helpers import apology, login_required, lookup, usd, pw_requirements

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #symbol, total shares, transaction type
    stocks = db.execute("SELECT stock_symbol, SUM(shares) as total_shares, type FROM transactions WHERE users_id == ? GROUP BY stock_symbol HAVING (SUM(shares) > 0);", session["user_id"])
    #user's cash
    cash = db.execute("SELECT cash FROM users WHERE id == ?;", session["user_id"])
    #set user's cash from stocks only = 0 to start
    total_stock_cash = 0

    for stock in stocks:
        quote = lookup(stock["stock_symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["total"] = stock["total_shares"] * stock["price"]
        total_stock_cash = total_stock_cash + stock["total"]

    total_cash = cash[0]["cash"] + total_stock_cash

    return render_template("index.html", cash=cash[0], stocks=stocks, total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        #define stock symbol, number of shares, stock price
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        stock = lookup(symbol)
        price = stock["price"]

        #define user cash before purchase, cost of purchase, cash after purchase
        pre_cash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]
        total_cost = stock["price"] * shares
        cash_left = pre_cash - total_cost

        if not symbol:
            return apology("No symbol provided")

        elif stock == None:
            return apology("Stock symbol could not be found")

        elif shares <= 0:
            return apology("Select a positive, whole number of shares to buy")

        elif pre_cash < total_cost:
            return apology("You do not have enough cash to make this purchase")

        else:
            #update cash left in users table
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_left, session["user_id"])
            #insert new transaction into transactions table
            db.execute("INSERT INTO transactions (users_id, stock_symbol, stock_price, shares, total_cost, type) VALUES (?, ?, ?, ?, ?, ?);", session["user_id"], symbol.upper(), price, shares, total_cost, "buy")

            return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM transactions WHERE users_id = ?;", session["user_id"])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("No symbol provided")

        stock = lookup(symbol)
        if stock == None:
            return apology("Stock symbol could not be found")

        return render_template("quoted.html", name = stock["name"], price = usd(stock["price"]), symbol = stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        username = request.form.get("username")

        if not username:
            return apology("No username provided")
        if not password:
            return apology("No password provided")

        valid_pw = pw_requirements(password)
        if valid_pw == 0:
            return apology("Password must have min of six characters and max of twenty, at least one number, and at least one of $#@")

        if not confirmation:
            return apology("No confirmation provided")

        if password != confirmation:
            return apology("Your password and confirmation are not the same")

        hash = generate_password_hash(confirmation)

        #python version of do-while loop
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("Username already taken")

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if int(shares) < 1:
                return apology("input a positive integer for shares")

        if not symbol:
            return apology("No symbol inputted")

        stocks = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE users_id = ? AND symbol = ?;", session["user_id"], symbol)[0]

        if shares > stocks["total_shares"]:
            return apology("You don't have enough shares")
        stock = lookup(symbol)
        price = stock["price"]
        total_value = price * shares

        db.execute("INSERT INTO transactions (users_id, stock_symbol, shares, stock_price, type) VALUES (?, ?, ?, ?, ?);",
        session["user_id"], symbol.upper(), -shares, price, "sell")

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_value, session["user_id"])

        flash("Sold")
        return redirect("/")
    else:
        stocks = db.execute("SELECT stock_symbol FROM transactions WHERE users_id = ? GROUP BY stock_symbol;", session["user_id"])
        return render_template("sell.html", stocks=stocks)

#export API_KEY=pk_efcdfe0036634f20af0b75c583bcc4e2

