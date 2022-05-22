
--CRIME DESCRIPTION
/*SELECT description FROM crime_scene_reports
WHERE crime_scene_reports.month = 7
AND crime_scene_reports.day = 28
AND crime_scene_reports.year = 2021
AND street = "Humphrey Street"; */

--INTERVIEWS
/*SELECT transcript, name FROM interviews
WHERE (month = 7) AND (day = 28) AND (year = 2021) AND (transcript LIKE "%bakery%"); */


--PART 1: NAME OF THIEF
SELECT name FROM people

--PHONE CALLS
WHERE people.phone_number IN (
        SELECT caller FROM phone_calls
        WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28
        AND duration < 60
)
--suspects: Kenny, Sofia, Benista, Taylor, Diana, Kelsey, Bruce, Carina

--BAKERY SECURITY LOGS
AND people.license_plate IN (
        SELECT bakery_security_logs.license_plate FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15
        AND activity = "exit"
)
--suspects left: Sofia, Diana, Kelsey, Bruce

--ATM TRANSACTIONS
AND people.id IN (
        SELECT person_id FROM bank_accounts
        JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
        JOIN people ON people.id = bank_accounts.person_id
        WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28
        AND transaction_type = "withdraw"
        AND atm_location = "Leggett Street"
)
--suspects left: Diana, Bruce

AND people.passport_number IN (

        SELECT passport_number FROM passengers
        JOIN flights ON passengers.flight_id = flights.id
        WHERE passengers.flight_id = (
                SELECT id FROM flights
                WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29
                AND flights.origin_airport_id = (
                        SELECT id FROM airports
                        WHERE city = "Fiftyville")
                ORDER by flights.hour, flights.minute LIMIT 1
        )
);

--suspects left: Bruce

--PART 2: CITY THIEF ESCAPED TO

SELECT city FROM airports
WHERE airports.id IN (
        SELECT destination_airport_id FROM flights
        WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29
        AND flights.origin_airport_id = (
                SELECT id FROM airports
                WHERE city = "Fiftyville")
        ORDER by flights.hour, flights.minute LIMIT 1
);

--Destination: NYC

--PART 3: NAME OF ACCOMPLICE

SELECT name FROM people
WHERE phone_number IN (
        SELECT receiver FROM phone_calls
        WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND duration < 60
        AND caller IN (
                SELECT phone_number FROM people
                WHERE name = "Bruce"
        )
);











