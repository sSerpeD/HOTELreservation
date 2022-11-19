# reservation.c
#### Video Demo:  <https://youtu.be/0bL0EsG_tMk>
#### Description: This program will ask user for input num1 or num2 (Hotel or Guest).
#### If user input num1 (Hotel) The program will ask the name of the hotel.
#### If Hotel name not exist then append hotelname in HOTEL.txt and ask for room amount.
#### Then create a file call (thatHotelname).txt and append '0' (vacant) equal too room amount.
#### If Hotel name exist then ask user if they want to delete all data or not.
#### If input == 'Y' then rewrite (thatHotelname).txt and append '0' (vacant) equal too room amount.
#### else if input == 'N' then do nothing.
#### Then program will go back to first page that ask user for input num1 or num2 (Hotel or Guest).
#### If user input num2 (Guest) The program will ask the name of the hotel.
#### If Hotel name not exist then prompt user "Not existed" then go back too first page.
#### If Hotel name exist then ask user how many room they want to reserved.
#### Example: user input = 5 then program will go to (thatHotelname).txt and clear all data.
#### write 1 equal to room reserved then add 0 for the room left.
## Hotel Reservation Program

#### This is my cs50 finale project.
# This is CS50.
