import logging
logging.basicConfig(format='%(message)s', level=logging.INFO)
"""
* This function will take an input and run the conditional functions from *args

* input_message: str
   - This is the message that will appear when asking for input

* err_message: str
   - This is the message that will appear if an error occurs

* returnType=str
   - This is the type that will be returned from this function, it defaults to str

* *args: callable
   - This will contain the all the conditional callables that should be 
    called to ensure the validity of the data
"""
def get_and_validate(*args: callable,
                     input_message: str = "",  
                     err_message: str = "",
                     return_type: type = str) -> any:
   
   value = input(input_message)
   for func in args:
      if not func(value):
         logging.error(err_message);
         raise Exception;
   return return_type(value);