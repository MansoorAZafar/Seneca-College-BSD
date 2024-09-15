import vars;
from database import Database;
from colorama import Fore

line = lambda : print(f'\n{Fore.GREEN}----------------------------------------------\n')
def reset(db):
    for i in range(1,51):
        db.db_remove_reservation(Slot_ID=i);
    
def pause():
    input(f'{Fore.RED} ... Press enter to continue the tests ...')
    line();

if __name__ == "__main__":
    
    # Initialize the database:
    #######################################
    """ INITIALIZATION OF THE DATABASE """
    #######################################
    print(f'{Fore.RED}Initializing the Database:{Fore.GREEN}')
    db = Database(vars.connection_string, 20, 30);
    print(f'{Fore.GREEN}Success')
    line();


    pause();


    #######################################
    """ ADDING PEOPLE INTO THE DATABASE """
    #######################################
    print(f'{Fore.RED}Adding People:\n{Fore.GREEN}');
    # Adding People:
    try:
        db.db_add_user(username="One", password="password 1");
        db.db_add_user(username="Two", password="2nd password");
        db.db_add_user("Three", "The 3rd Password");
    except:
        print(f'If this is the 2nd time you\'re running the program, then this is okay.');
    line();


    pause();



    #######################################
    """ GETTING THE USER """
    #######################################
    print(f'{Fore.RED}... Confirming People Exist ...:\n{Fore.GREEN}');
    if db.db_get_user("One"):
        print(f'{Fore.GREEN}Success')
    line();
    
    

    pause();

    
    #######################################
    """ VIEWING ALL FREE PARKING SPACES"""
    #######################################
    print(f'{Fore.RED}Viewing ALL open Parking Spaces\n');
    # Viewing the Open Locations:
    all_spaces = db.db_get_available_locations(condition="all"); # Returns all open spaces in the 
    for space in all_spaces:
        print(f'{Fore.BLUE}  All Spaces : {Fore.WHITE}{space}');
    line();



    pause();


    ############################################
    """ VIEW ALL THE "INNER" PARKING SPACES """
    ############################################
    print(f'{Fore.RED}Viewing INNER open Parking Spaces\n');
    inner_spaces = db.db_get_available_locations(condition="iNneR");
    for space in inner_spaces:
        print(f'{Fore.BLUE}  Inner Spaces : {Fore.WHITE}{space}');
    line();



    pause();


    ############################################
    """ VIEW ALL THE "OUTER" PARKING SPACES """
    ############################################
    print(f'{Fore.RED}Viewing OUTER open Parking Spaces\n');
    outer_spaces = db.db_get_available_locations("OUTER");
    for space in outer_spaces:
        print(f'{Fore.BLUE}  Outer Spaces : {Fore.WHITE}{space}');
    
    line();



    pause();


    #######################################
    """ RESERVE SPACES """
    #######################################
    print(f'{Fore.RED}Reserving Spaces {Fore.GREEN}\n');
    try:
        for i in range(31, 51):
            db.db_add_reservation("Two", i, 12);
        db.db_add_reservation(username="One", slot_id=1, expiry_hours=1);
        db.db_add_reservation(username="One", slot_id=15, expiry_hours=3.2);
        db.db_add_reservation(username="Two", slot_id=30, expiry_hours=55);
        db.db_add_reservation(username="Three", slot_id=5, expiry_hours=5);
        db.db_add_reservation(username="Three", slot_id=1, expiry_hours=11);        
    except:
        print(f'{Fore.RED} ...This Message Should Appear...')
    line();
    


    pause();


    #######################################
    """ GETTING A [USER]'S RESERVATIONS """
    #######################################
    print(f'{Fore.RED}Seeing all of User "Two" Reservations {Fore.GREEN}\n');
    reservations = db.db_get_your_reservations(username="Two");
    for res in reservations:
        print(f'  {Fore.BLUE}{res}');
    line();
    
    
    
    pause();
    
    
    #######################################
    """ GETTING ALL FREE SPACES """
    #######################################
    print(f'{Fore.RED}Viewing All Free Spaces {Fore.BLUE}\n');
    all_spaces = db.db_get_available_locations(condition="all"); # Returns all open spaces in the 
    for space in all_spaces:
        print(f'{Fore.BLUE}  All Spaces : {Fore.WHITE}{space}');
    line();
    
    
    
    pause();
    
    
    #######################################
    """ REMOVING RESERVATIONS """
    #######################################
    print(f'{Fore.RED}Removing Reservations [1-20] {Fore.GREEN}\n');
    for i in range(1, 21):
        db.db_remove_reservation(Slot_ID=i);
    line();
    
    
    
    pause();
    
    
    #######################################
    """ SEEING ALL THE FREE SPACES """
    #######################################
    print(f'{Fore.RED}Viewing All Free Spaces {Fore.BLUE}\n');
    all_spaces = db.db_get_available_locations(condition="all"); # Returns all open spaces in the 
    for space in all_spaces:
        print(f'{Fore.BLUE}  All Spaces : {Fore.WHITE}{space}');
    line();
    
    
    pause();
    
    
    #######################################
    """ ADDED COMMENT FOR A SPECIFIC SLOT """
    #######################################
    print(f'{Fore.RED}Adding Comments {Fore.GREEN}\n');
    for i in range(1,10):
        db.db_add_comment(comment=f'  This is the {i} Comment', SlotID=i);
    line();
    
    
    pause();
    
    
    
    #######################################
    """ VIEWING ALL THE COMMENTS FOR ANY SLOT """
    #######################################
    print(f'{Fore.RED}Viewing Comments {Fore.BLUE}\n');
    for i in range(1, 10):
        print(db.db_get_comments(SlotID=i));
    line();
    
    
    
    pause();
    
    
    #######################################
    """ RESETING FOR TESTS """
    #######################################
    print(f'{Fore.RED}Removing All Reservations for next test run... {Fore.GREEN}\n');
    for i in range(1, 51):
        db.db_remove_reservation(Slot_ID=i);
    line();
    
    
    pause();
    
    
    
    #######################################
    """ END """
    #######################################
    print(f'{Fore.RED}!!!   Congratulations! You\'ve Finished All the Tests   !!! {Fore.RESET}\n');



