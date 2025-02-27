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
This section outlines how to interact with the Backend API developed by Mansoor Zafar.
