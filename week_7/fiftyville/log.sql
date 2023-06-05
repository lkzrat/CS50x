-- All you know is that the theft took place on ((((July 28, 2021)))) and that it took place on ((((Humphrey Street)))).

-- Getting crime information with the info that was given
SELECT *
FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

-- There are 2 crimes with this infos, id = (295, 297)

-- Getting the description of this 2 crimes
SELECT id, description
FROM crime_scene_reports
WHERE id = 295
OR id = 297;

-- Crime id = 295
-- Description = Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--               Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Getting interviews info that said something about a bakery
SELECT *
FROM interviews
WHERE transcript LIKE '%bakery%';

-- Interviesws:

-- 161 - Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--        If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- 162 - Eugene: I don't know the thief's name, but it was someone I recognized.
--               Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- 163 - Kiana: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--              I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--              The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- New info:
-- Cars at 10 past 10:15 am
-- Emma's bakery / ATM, Legget Street ... withdrawing money
-- flights at july 29, 2018


-- ALL possible plates
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25;

-- ALL possible phone numbers
SELECT caller
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

-- ALL possible person ids
SELECT *
FROM perosn_id
WHERE account_number IN(
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
);

-- ALL possible passport
SELECT passport_number
FROM passengers
WHERE flight_id IN(
    SELECT id
    FROM flights
    WHERE origin_airport_id IN(
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
    AND year = 2021
    AND month = 7
    AND day = 29
    AND hour = 8
);

-- Finding the thief
SELECT *
FROM people
WHERE license_plate IN(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
    AND activity = 'exit'
)
AND phone_number IN(
    SELECT caller
    FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
)
AND id IN(
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN(
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
)
AND passport_number IN(
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN(
        SELECT id
        FROM flights
        WHERE origin_airport_id IN(
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        AND year = 2021
        AND month = 7
        AND day = 29
        AND hour = 8
    )
);

-- THIEF FOUND, ALL INFO:
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- Getting the city who the thief escaped to
SELECT city
FROM airports
WHERE id IN(
    SELECT destination_airport_id
    FROM flights
    WHERE id IN(
        SELECT id
        FROM flights
        WHERE origin_airport_id IN(
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        AND year = 2021
        AND month = 7
        AND day = 29
        AND hour = 8
    )
);

-- CITY FOUND: New York City

-- Getting the accomplice number
SELECT receiver
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
AND caller = '(367) 555-5533';

-- (375) 555-8161

-- Getting accomplice info
SELECT *
FROM people
WHERE phone_number = '(375) 555-8161';

-- ACCOMPLICE FOUND, ALL INFO:
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
-- +--------+-------+----------------+-----------------+---------------+