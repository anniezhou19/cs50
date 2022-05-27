-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports
WHERE year = '2020' AND month = 7 AND day = 28 AND street = 'Chamberlin Street';

--Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
--Interviews were conducted today with three witnesses who were present at the time
--— each of their interview transcripts mentions the courthouse.

SELECT * FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28;
id | name | year | month | day | transcript
158 | Jose | 2020 | 7 | 28 | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
159 | Eugene | 2020 | 7 | 28 | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
160 | Barbara | 2020 | 7 | 28 | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
--Thief might have a german name
--find suspect's names through license_plate:
SELECT * FROM courthouse_security_logs JOIN people 
ON courthouse_security_logs.license_plate = people.license_plate
WHERE courthouse_security_logs.year = 2020 AND courthouse_security_logs.month = 7
AND courthouse_security_logs.day = 28 AND courthouse_security_logs.hour = 10
AND courthouse_security_logs.minute > 15 AND courthouse_security_logs.minute <= 25;

id | year | month | day | hour | minute | activity | license_plate | id | name | phone_number | passport_number | license_plate
260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95 | 221103 | Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2 | 243696 | Amber | (301) 555-4174 | 7526138472 | 6P58WS2
263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8 | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7 | 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ | 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE | 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55 | 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55

--find suspect names through phone_call:
SELECT * FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number
WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 
AND phone_calls.duration <= 60;

id | caller | receiver | year | month | day | duration | id | name | phone_number | passport_number | license_plate
221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51 | 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36 | 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45 | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
234 | (609) 555-5876 | (389) 555-5198 | 2020 | 7 | 28 | 60 | 561160 | Kathryn | (609) 555-5876 | 6121106406 | 4ZY7I8T
251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50 | 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43 | 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49 | 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38 | 907148 | Kimberly | (031) 555-6622 | 9628244268 | Q12B3Z3
279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55 | 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54 | 438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
--suspect might be: Ernest, Roger, Russell, Evelyn

--find suspect thief names through bank_account:
SELECT * FROM atm_transactions JOIN bank_accounts 
ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Fifer Street' ORDER BY people.name; 

id | account_number | year | month | day | atm_location | transaction_type | amount | account_number | person_id | creation_year | id | name | phone_number | passport_number | license_plate
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20 | 28296815 | 395717 | 2014 | 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48 | 28500762 | 467400 | 2014 | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20 | 25506511 | 396669 | 2014 | 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50 | 49610011 | 686048 | 2010 | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60 | 76054385 | 449774 | 2015 | 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
275 | 86363979 | 2020 | 7 | 28 | Fifer Street | deposit | 10 | 86363979 | 948985 | 2010 | 948985 | Robert | (098) 555-1164 | 8304650265 | I449449
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80 | 16153065 | 458378 | 2012 | 458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35 | 26013199 | 514354 | 2012 | 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30 | 81061156 | 438727 | 2018 | 438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
--suspect now:Ernest, Russell

--find the earliest flight:
SELECT * FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour;
id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
--flights id: 36
--find the city to escape: London
SELECT * FROM airports JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.destination_airport_id = 4;
--escape to city: London

SELECT * FROM passengers JOIN flights ON passengers.flight_id = flights.id
JOIN people ON passengers.passport_number = people.passport_number
WHERE flights.id = 36 AND flights.year = 2020 AND flights.month = 7 AND flights.day = 29 
ORDER BY people.name;

flight_id | passport_number | seat | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | id | name | phone_number | passport_number | license_plate
36 | 9878712108 | 7A | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
36 | 8496433585 | 7B | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
36 | 7214083635 | 2A | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 953679 | Doris | (066) 555-9701 | 7214083635 | M51FA04
36 | 1540955065 | 5C | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 651714 | Edward | (328) 555-1152 | 1540955065 | 130LD9Z
36 | 5773159633 | 4A | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
36 | 8294398571 | 6C | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
36 | 1988161715 | 6D | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
36 | 1695452385 | 3B | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
--The thief is Ernest
--Find the accomplice through phone call receiver:
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
id | name | phone_number | passport_number | license_plate
864400 | Berthold | (375) 555-8161 |  | 4V16VO0
--The accomplice is Berthold