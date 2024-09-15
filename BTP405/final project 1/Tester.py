import vars;
from database import Database;

if __name__ == "__main__":
    
    

    MAX_INNER = 20;
    db = Database(vars.connection_string, 20, 30);
    
    print(db.get_type_of_slot(10));
    
     
    print(db.authenticate_user("One", "password 1"));
    print(db.authenticate_user("test1", "test1"));
    print(db.authenticate_user("Hello", "World"))




