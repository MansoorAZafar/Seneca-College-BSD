import logging
logging.basicConfig(format='%(message)s', level=logging.INFO)
class Account:
    def __init__(self, 
                 name: str, 
                 balance: float):
        """
        * Default initalizer of this class takes a name and balance
        * 
        * name: str
            - the name of the account holder 
        * balance: float
            - the initial balance of the account
        * -------
        * Note  |
        * -------
        * The values are and should be validated before coming into this
        """
        self.name = name;
        self.balance = balance;

    def deposit(self, 
                amount: float):
        self.balance += amount;
        logging.info("Deposit successful.")

    def withdraw(self, 
                 amount: float):
        self.balance -= amount;
        logging.info("Withdrawal successful.")

    def get_balance(self):
        return self.balance;