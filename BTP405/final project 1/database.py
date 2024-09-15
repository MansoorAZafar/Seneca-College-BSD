import threading
import time
import mysql.connector
import vars;

"""
* A Python Module to connect, read and update a MySQL database. 
* The features include:
 - Adding/Getting Comments
 - Getting Available Parking Spaces
 - Getting/Authenticating/Adding a User
 - Getting the Type of the parking space
 - Adding/Removing/Getting Reservations
 - Initialization of the SQL Tables 
 - Automatic deletion of old Reservations
"""
class Database: 
    #Connects to the database, creates the tables and initializes the automatic deletion thread
    """
    * Parameters
      > conn_str  : The Connection Dictionary containing the Database information 
      > maxInner : The Number of Parking Spaces that occupy the "Inner" Space
      > maxOuter: The Number of Parking Spaces that occupy the "Outer" Space
    """
    def __init__(self, conn_str, maxInner, maxOuter):
        self.connection = mysql.connector.connect(**conn_str)
        self.cursor = self.connection.cursor()
        self.maxInner = maxInner
        self.maxOuter = maxOuter
        self.expiry_thread = threading.Thread(target=self.__check_reservation_expiry)
        self.expiry_thread.daemon = True
        self.__createTables()
    
    #Ensure the closure of the resources & connection in a safe way
    def close_resources(self):
        self.cursor.close()
        self.connection.close()

    # Call after all modifications 
    #This function will clear the cursor for any potential existing queries/values left remaining on the cursor.
    def __clear_cursor(self):
        self.cursor.fetchall();
    
    """
    * Adds the specified comment to the specified Parking slot into the "Comments" table 
    * Parameters
    *  > comment : A String containing the text to be added as the content for the Comment
    *  > SlotID : A Integer containing the ID of the desired Parking Slot to be associate the comment with
    *
    Example:
    * SLOT_ID = 10
    * COMMENT = "Hello, this is a comment for The Parking Space 10"
    * Database.db_add_comment(COMMENT, SLOT_ID)
    """
    def db_add_comment(self, comment, SlotID):
        query = "INSERT INTO Comments (description, Slot_ID) VALUES (%s, %s)"
        self.cursor.execute(query, (comment, SlotID))
        self.connection.commit()
        print('Successfully added comment...')
        self.__clear_cursor();

    """
    * Returns a list with all the comments associated with the specified Slot
    * Parameters-
    *    > SlotID : A Integer containing the ID of the desired Parking Slot to get the comments from
    *
    * Example
    *   SLOT_ID = 10
    *   print(Database.db_get_comment(SLOT_ID))
    """
    def db_get_comments(self, SlotID):
        query = "SELECT * FROM Comments WHERE Slot_ID = %s"
        self.cursor.execute(query, (SlotID,))
        return self.cursor.fetchall()

    """
    * > Returns a list of tuples with all the Parking spaces that aren't booked and follow the condition. 
    * The tuple is made up of: 
    *  - Parking Slot ID, 
    *  - type of parking space 
    *  - Bit (0 or 1) to check if it is reserved
    * 
    * By default, this will return all free parking spaces, 
    * regardless of the type of parking space (inner/outer).
    *  - Caps do not matter.
    *  - A 'free booking space' is a space that isn't reserved.
    *
    *--------------
    * Note: the Bit is used to determine if the Slot is free or not 
    * (1 = true, 0 = false), this will automatically be updated when reserved 
    * and all values returned should have 0.
    *--------------
    * Parameters
    *  - Condition : A String detailing which free Parking spaces to return.
            - condition="inner" : Returns a list with all the free "inner" parking spaces 
            - condition="outer" : Returns a list with all the free "outer" parking spaces
            - condition="all"   : Returns a list with 'ALL' free parking spaces 
    
    * Example
    *    print(f'Viewing ALL open Parking Spaces\n');
    *    all_spaces = Database.db_get_available_locations(condition="all") 
    *    # Returns 'all' open spaces as a LIST
    *    for  space  in  all_spaces:
    *        print(f'All Spaces : {space}')
    *        
    *    ##################################################################
    *    print(f'Viewing OUTER open Parking Spaces\n');
    *    all_spaces = Database.db_get_available_locations(condition="OUTER") 
    *    # Returns 'outer' open spaces as a LIST
    *    for  space  in  all_spaces:
    *        print(f'All Spaces : {space}')
    *        
    *    ##################################################################
    *    print(f'Viewing INNER open Parking Spaces\n');
    *    all_spaces = Database.db_get_available_locations(condition="iNneR") 
    *    # Returns 'inner' open spaces as a LIST
    *    for  space  in  all_spaces:
    *        print(f'All Spaces : {space}')
    * 
    """

    def db_get_available_locations(self, condition="all"):
        match condition.lower():
            case "inner":
                query = "SELECT * FROM ParkingLots WHERE type = %s AND booked = %s";
                self.cursor.execute(query, ("inner", 0,));
            case "outer":
                query = "SELECT * FROM ParkingLots WHERE type = %s AND booked = %s";
                self.cursor.execute(query, ("outer", 0,));
            case _:
                query = "SELECT * FROM ParkingLots WHERE booked = %s";
                self.cursor.execute(query, (0,));
        return self.cursor.fetchall();

    """
    ********************************************
    * User Functions
    * get user
    * add user 
    """
    def db_get_user(self, username):
        query = "SELECT username FROM Consumer WHERE username = %s"
        self.cursor.execute(query, (username,))
        res = self.cursor.fetchone()
        self.__clear_cursor();
        print(f'res is {res}')
        return res;


    def get_type_of_slot(self, slotID):
        query = "SELECT type from ParkingLots WHERE SlotID = %s";
        self.cursor.execute(query, (slotID,));
        res = self.cursor.fetchone();
        self.__clear_cursor();
        return res;

    def authenticate_user(self, username, password):
        query = "SELECT username, password FROM Consumer WHERE username = %s AND password = %s";
        self.cursor.execute(query, (username, password,))
        res = self.cursor.fetchone();
        self.__clear_cursor();
        return res;

    def db_add_user(self, username, password):
        if self.db_get_user(username):
            raise Exception("User already exists")
        query = "INSERT INTO Consumer (username, password) VALUES (%s, %s)"
        self.cursor.execute(query, (username, password))
        self.connection.commit()
        self.__clear_cursor();

    """
    ********************************************
    * Reservation Functions
    * remove reservation
    * get reservations
    * add reservation
    """
    def db_remove_reservation(self, Slot_ID):
        query = "DELETE FROM Reservations WHERE Slot_ID = %s"
        self.cursor.execute(query, (Slot_ID,))
        query = "UPDATE ParkingLots SET booked = 0 WHERE SlotID = %s"
        self.cursor.execute(query, (Slot_ID,))
        self.connection.commit()
        print("Reservation removed successfully")
        self.__clear_cursor();

    def db_get_your_reservations(self, username):
        query = """
        SELECT r.* 
        FROM Reservations AS r
        INNER JOIN Consumer AS c ON c.username = %s
        WHERE r.userID = c.UID 
        """
        self.cursor.execute(query, (username,))
        return self.cursor.fetchall()

    def db_add_reservation(self, username, slot_id, expiry_hours):
        query = "SELECT booked FROM ParkingLots where SlotID = %s"
        self.cursor.execute(query, (slot_id,))
        res = self.cursor.fetchone()
        self.__clear_cursor();
        if res[0] == 1:
            raise Exception("Slot is already booked")

        query = "SELECT hourly_increase FROM Price INNER JOIN ParkingLots ON Price.type = ParkingLots.type WHERE ParkingLots.SlotID = %s"
        self.cursor.execute(query, (slot_id,))
        price_info = self.cursor.fetchone()
        self.__clear_cursor();

        if price_info:
            query = "UPDATE ParkingLots SET booked = 1 WHERE SlotID = %s";
            self.cursor.execute(query, (slot_id,));
            self.__clear_cursor();
            hourly_increase = price_info
            initial_price = hourly_increase * expiry_hours
            insert_query = "INSERT INTO Reservations (price, expiry, Slot_ID, userID) VALUES (%s, DATE_ADD(NOW(), INTERVAL %s HOUR), %s, (SELECT UID FROM Consumer WHERE username = %s))"
            self.cursor.execute(insert_query, (initial_price, expiry_hours, slot_id, username))
            self.connection.commit()
            self.__clear_cursor();
        else:
            raise Exception("Slot type not found in Price table")

        print("Reservation added successfully")

    """
    ******************************************************************
    * This function will create the tables, initialize the 
    * data for the ParkingLots table and startup the expiry thread
    *************************
    * Table Initializations
    * Thread Func Initialization
    """
    def __createTables(self):
        try:
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS Consumer (
                    UID INT AUTO_INCREMENT PRIMARY KEY,
                    username varchar(30) NOT NULL,
                    password varchar(30) NOT NULL
                )
            """)

            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS ParkingLots (
                    SlotID INT AUTO_INCREMENT PRIMARY KEY,
                    type varchar(10) NOT NULL,
                    booked BIT DEFAULT 0
                )
            """)

            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS Comments (
                    ID INT AUTO_INCREMENT PRIMARY KEY,
                    description varchar(250),
                    Slot_ID INT,
                    FOREIGN KEY (Slot_ID) REFERENCES ParkingLots(SlotID)
                )
            """)

            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS Price (
                    type varchar(10) PRIMARY KEY,
                    hourly_increase FLOAT 
                )
            """)

            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS Reservations (
                    ID INT AUTO_INCREMENT PRIMARY KEY,
                    price FLOAT,
                    expiry DATETIME,
                    Slot_ID INT,
                    userID INT,
                    FOREIGN KEY (Slot_ID) REFERENCES ParkingLots(SlotID),
                    FOREIGN KEY (userID) REFERENCES Consumer(UID)
                )
            """)

            self.expiry_thread.start()

            self.cursor.execute("SELECT * FROM ParkingLots")
            output = self.cursor.fetchone()
            self.__clear_cursor();
            if output:
                print(f'output: {output}')
                print(f'Leaving Early... (as you should...)')
                return
            
            insertQuery = "INSERT INTO ParkingLots (type) VALUES (%s)"
            for i in range(1, self.maxInner + 1):
                self.cursor.execute(insertQuery, ("inner",))

            for i in range(1, self.maxOuter + 1):
                self.cursor.execute(insertQuery, ("outer",))
            
            insertQuery = "INSERT INTO Price (type, hourly_increase) VALUES (%s, %s)"

            self.cursor.execute(insertQuery, ("inner", 2.35,))
            self.cursor.execute(insertQuery, ("outer", 4.32,))
            
            self.connection.commit();
        except Exception as e:
            print("Error in initialize_db:", e)

    def __check_reservation_expiry(self):
        conn = None
        cursor = None
        try:
            # Create a new connection and cursor inside the thread
            conn = mysql.connector.connect(**vars.connection_string)
            cursor = conn.cursor()

            while True:
                try:
                    # Your existing code for handling reservations expiry
                    query = "DELETE FROM Reservations WHERE expiry <= NOW()"
                    cursor.execute(query)
                    query = "UPDATE ParkingLots SET booked = 0 WHERE SlotID NOT IN (SELECT Slot_ID FROM Reservations)"
                    cursor.execute(query)
                    conn.commit()
                    time.sleep(3600 * 3)  # Sleep for 3 hours
                except Exception as e:
                    print("Error in check_reservation_expiry:", e)
        finally:
            # Close the cursor and connection when the thread exits
            if cursor:
                cursor.close()
            if conn:
                conn.close()

