# Django-Flask-Parking-Application

The Parking Simulator application offers users access to 50 distinct slots, categorized into 'inner' and 'outer' spaces for reservation. Users can effortlessly manage their bookings, provide feedback, and access authentication features such as login, logout, and registration. The backend API, developed using Django by Mansoor Zafar, handles reservation management, while the frontend UI, implemented using Flask by Aldrin Fernandez, allows users to interact with the system. Nazanin Tabrizizadeh conducted frontend tests, and Mansoor Zafar performed backend tests.


## Usage

To access the application, simply visit the following URL:
[https://project2-2.onrender.com/](https://project2-2.onrender.com/)


## Screenshots

- Starting Screen:

  ![image](https://github.com/MansoorAZafar/Django-Flask-Parking-Application/assets/164381371/1fa7033a-8f41-4709-8d9d-d438213c2cb3)

- Login:

  ![image](https://github.com/MansoorAZafar/Django-Flask-Parking-Application/assets/164381371/67396012-5739-4be3-b156-2c9f97b0cda5)

- Main Menu:

  ![image](https://github.com/MansoorAZafar/Django-Flask-Parking-Application/assets/164381371/e60f84d5-dd96-4800-8b99-c221574f3c63)

- Showing Parking Spaces:

  ![image](https://github.com/MansoorAZafar/Django-Flask-Parking-Application/assets/164381371/d0a5daf0-bf89-4051-91a6-57dc7b6e1ac8)

- Reserving:

  ![image](https://github.com/MansoorAZafar/Django-Flask-Parking-Application/assets/164381371/78fb43aa-1655-4cdc-9d94-43654b75d993)

- Viewing Reservations:

  ![image](https://github.com/MansoorAZafar/Django-Flask-Parking-Application/assets/164381371/204d936c-0a62-4948-81c1-240345db5178)

## Features

- Login
- Register
- Reserve parking spaces
- View available parking spaces
- View reservations
- View inner and outer parking spaces
- Leave feedback
- Logout

## Contributing & Credits

- **UI:** Aldrin Fernandez [@aldrin118](https://github.com/aldrin118)
  - Implemented frontend components and UI design.

- **Frontend Tests** Nazanin Tabrizizadeh [@naz-tbz](https://github.com/naz-tbz)
  - Implemented testR.py

- **Backend Tests:** Mansoor Zafar [@MansoorAZafar](https://github.com/MansoorAZafar) or [@Mansoor-A-Zafar](https://github.com/Mansoor-A-Zafar) (School Account)
  - Conducted tests for the backend API.

- **Database API:** Mansoor Zafar
  - Developed the backend API for managing and creating parking features.
  - Developed all backend logic of the API
  - Dockerized the application and hosted it on the cloud using Render.

## Database Hosting

The database is hosted online using Clever Cloud MySQL.
[https://www.clever-cloud.com/product/mysql/](https://www.clever-cloud.com/product/mysql/)

The Backend API is hosted online using Render
https://render.com/

## Backend API Usage

### Add Comment
- **Method:** POST
- **URL:** `https://database-api-latest.onrender.com/myapp/add_comment/`
- **Body:** 
```json
  {
    "comment": "text",
    "slot_id": 1
  }
```
Successful Output:
```json
{
  "message": "Comment added successfully"
}
```
Bad Output:
```json
{
  "error": "Invalid request method"
}
```
### Get Comments
- **Method:** GET
- **URL:** `https://database-api-latest.onrender.com/myapp/get_comments/?slot_id=[number]`
Successful Output:
```json
[
  {
    "id": 1,
    "description": "Hello World! This is for slot 1",
    "Slot_ID_id": 1
  }
]
```
Bad Output:
```json
[]
```
### Get Available Locations
- **Method:** GET
- **URL:** `https://database-api-latest.onrender.com/myapp/get_available_locations/?condition=[type of condition]`
- **Types of conditions:** all (default), inner, outer
  - (if you just do the URL without ?condition=, it defaults to all)
Successful Output:
```json
{
  "available_locations": [
    {
      "id": 1,
      "type": "inner",
      "booked": false
    },
    {
      "id": 2,
      "type": "inner",
      "booked": false
    },
    ...
  ]
}
```
### Slot Type
- **Method:** GET
- **URL:** `https://database-api-latest.onrender.com/myapp/slot_type/?slot_id=[number]`
Successful Output:
```json
{
  "slot type is ": "inner"
}
```
Bad Output: (Status: 403 Forbidden)
```json
{
  "error": "Slot does not exist"
}
```
### Authenticate User
- **Method:** GET
- **URL:** `https://database-api-latest.onrender.com/myapp/authenticate_user/?username=[username]&password=[password]`
Successful Output:
```json
{
  "success": true,
  "user": {
    "id": 1,
    "username": "One",
    "password": "test1"
  }
}
```
Bad Output: (Status 403 Forbidden)
```json
{
  "error": "Invalid Credentials"
}
```
### Add User
- **Method:** POST
- **URL:** `https://database-api-latest.onrender.com/myapp/add_user/`
- **Body:**
```json
{
  "username": "two",
  "password": "test2"
}
```
Successful Output:
```json
{
  "message": "User added successfully"
}
```
Bad Output: (Status 403 Forbidden)
```json
{
  "error": "User already Exists"
}
```
### Remove Reservation
- **Method:** DELETE
- **URL:** `https://database-api-latest.onrender.com/myapp/remove_reservation/`
- **Body:**
```json
{
  "slot_id": [number]
}
```
Successful Output:
```json
{
  "message": "Reservation removed successfully"
}
```
Bad Output: (Status 403 Forbidden)
```json
{
  "error": "No such Reservation"
}
```
## Get Your Reservations
- **Method:** GET
- **URL:** `https://database-api-latest.onrender.com/myapp/get_your_reservations/?username=[username]`
Successful Output (example):
```json
{
  "reservations": [
    {
      "id": 2,
      "price": 0.43200000000000005,
      "expiry": "2024-04-02T23:19:27.055Z",
      "Slot_ID_id": 23,
      "userID_id": 1
    }
  ]
}
```
Bad Output:
```json
{
  "reservations": []
}
```
### Add Reservation
- **Method:** POST
- **URL:** `https://database-api-latest.onrender.com/myapp/add_reservation/`
- **Body:**
```json
{
  "username": [user's username],
  "slot_id": [number],
  "expiry_hours": [number of hours]
}
```
Successful Output:
```json
{
  "message": "Reservation added successfully"
}
```
Bad Output:
```json
{
  "error": "Slot is already booked"
}
```
or
```json
{
  "error": "Slot not found"
}
```
