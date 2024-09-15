from Account import Account;
from Validator import get_and_validate
import logging

logging.basicConfig(format='%(message)s', level=logging.INFO)

class Bank:
    def __init__(self):
        self.accounts: dict = {};
    
    @staticmethod
    def __valid_amount(amount: any) -> bool:
        try: return float(amount) >= 0
        except: return False;

    def __account_exists(self, 
                         account_number: any) -> bool:
        return account_number.isnumeric() and int(account_number) in self.accounts;


    def create_account(self):
        try:
            name: str = input("Enter your name:\n> ");
            balance: float = get_and_validate(self.__valid_amount,
                                              input_message="Enter initial balance: ",
                                              err_message="Initial balance cannot be negative.",
                                              return_type=float);
            account_number: int = len(self.accounts) + 1;
            self.accounts[account_number] = Account(name, balance);
            
            logging.info(f"Account created successfully! Your account number is {account_number}")
        except:
            return;    

    def deposit(self):
        try:
            account_number = get_and_validate(self.__valid_amount,
                                              self.__account_exists,
                                              input_message="Enter account number: ",
                                              err_message="Account does not exist.",
                                              return_type=int)
            
            amount = get_and_validate(self.__valid_amount,
                                      input_message="Enter amount to deposit: ",
                                      err_message="Deposit amount cannot be negative.",
                                      return_type=float)
            self.accounts[account_number].deposit(amount);
        except Exception as e:
            return;

    def withdraw(self):
        try:
            account_number = get_and_validate(self.__valid_amount,
                                              self.__account_exists,
                                              input_message="Enter account number: ",
                                              err_message="Account does not exist.",
                                              return_type=int);
            
            amount = get_and_validate(self.__valid_amount,
                                      lambda amt, acc_num=account_number: float(amt) <= float(self.accounts[acc_num].get_balance()),
                                      input_message="Enter amount to withdraw: ",
                                      err_message="Withdrawal amount cannot be negative.",
                                      return_type=float)
            self.accounts[account_number].withdraw(amount);
        except:
            return;

    def view_balance(self):
        try:
            account_number = get_and_validate(self.__valid_amount,
                                              self.__account_exists,
                                              input_message="Enter account number: ",
                                              err_message="Account does not exist.",
                                              return_type=int);
            logging.info(f"Your balance is: {self.accounts[account_number].get_balance()}")
        except:
            return;

    