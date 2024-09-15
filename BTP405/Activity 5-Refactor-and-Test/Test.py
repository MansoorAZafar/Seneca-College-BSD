import unittest
from unittest import mock
from unittest import TestCase
from Account import Account
from Bank import Bank
from Validator import get_and_validate
import logging

class TestBank(TestCase):

    def setUp(self) -> None:
        self.mocked_input = mock.patch('builtins.input', create=True).start()
        self.bank: Bank = Bank()
        with mock.patch('logging.info') as mocked_print:
            self.mocked_input.side_effect = ['Test', '100']
            self.bank.create_account()
            mocked_print.assert_called_with(f"Account created successfully! Your account number is {len(self.bank.accounts)}")

    def tearDown(self) -> None:
        self.mocked_input.stop()

    def test_create_account(self):
        expected_person = {'Test': 100}
        expected_account_number = 1
        self.bank.create_account()
        self.assertEqual(expected_person, {self.bank.accounts[expected_account_number].name: self.bank.accounts[expected_account_number].balance})
        
    def test_create_account_bad_balance(self):
        self.mocked_input.side_effect = ['Tests', '-200']
        with mock.patch('logging.error') as mocked_print:
            self.bank.create_account();
            mocked_print.assert_called_once_with("Initial balance cannot be negative.")

    def test_deposit_positive_values(self):
        initial_balance = self.bank.accounts[1].balance
        # Mock user input for deposit
        self.mocked_input.side_effect = ['1', '20']

        # Mock print function to capture its output
        with mock.patch('logging.info') as mocked_print:
            self.bank.deposit()

            # Check if the balance increased by the deposited amount
            expected_balance = initial_balance + 20
            self.assertEqual(expected_balance, self.bank.accounts[1].balance)

            # Check if "Deposit successful." was printed
            mocked_print.assert_called_once_with("Deposit successful.")

    def test_deposit_bad_bal_and_acc_num(self):
        self.mocked_input.side_effect = ['1', '"-200"']
        with mock.patch('logging.error') as mocked_print:
            #Testing bad deposit values
            self.bank.deposit()
            mocked_print.assert_called_with("Deposit amount cannot be negative.")
            self.mocked_input.side_effect = ['1', '-200']
            self.bank.deposit()
            mocked_print.assert_called_with("Deposit amount cannot be negative.")
            
            #Testing bad account values
            self.mocked_input.side_effect = ['200', '-200']
            self.bank.deposit()
            mocked_print.assert_called_with("Account does not exist.")

            self.mocked_input.side_effect = ['"I am a sentence"', '-200']
            self.bank.deposit()
            mocked_print.assert_called_with("Account does not exist.")

    def test_withdraw(self):
        initial_balance = self.bank.accounts[1].balance
        self.mocked_input.side_effect = ['1', '20']
        with mock.patch('logging.info') as mocked_print:
            self.bank.withdraw()

            # Check if the balance increased by the deposited amount
            expected_balance = initial_balance - 20
            self.assertEqual(expected_balance, self.bank.accounts[1].balance)

            # Check if "Deposit successful." was printed
            mocked_print.assert_called_once_with("Withdrawal successful.")

    def test_withdraw_bad_bal_and_acc_num(self):
        self.mocked_input.side_effect = ['1', '"-200"']
        with mock.patch('logging.error') as mocked_print:
            #Testing bad withdrawal values
            self.bank.withdraw()
            mocked_print.assert_called_with("Withdrawal amount cannot be negative.")
            self.mocked_input.side_effect = ['1', '-200']
            self.bank.withdraw()
            mocked_print.assert_called_with("Withdrawal amount cannot be negative.")
            self.mocked_input.side_effect = ['1', '10000000000']
            self.bank.withdraw()
            mocked_print.assert_called_with("Withdrawal amount cannot be negative.")


            #Testing bad account values
            self.mocked_input.side_effect = ['200', '-200']
            self.bank.withdraw()
            mocked_print.assert_called_with("Account does not exist.")

            self.mocked_input.side_effect = ['"I am a sentence"', '-200']
            self.bank.withdraw()
            mocked_print.assert_called_with("Account does not exist.")

    def test_view_balance(self):
        expected_balance = self.bank.accounts[1].balance
        self.mocked_input.side_effect = ['1']
        with mock.patch('logging.info') as mocked_print:
            self.bank.view_balance();
            mocked_print.assert_called_with(f"Your balance is: {expected_balance}")

    def test_view_balance_bad(self):
        with mock.patch('logging.error') as mocked_print:
            
            #Testing bad account values
            self.mocked_input.side_effect = ['200']
            self.bank.view_balance()
            mocked_print.assert_called_with("Account does not exist.")

            self.mocked_input.side_effect = ['"I am a sentence"']
            self.bank.view_balance()
            mocked_print.assert_called_with("Account does not exist.")


class TestAccount(TestCase):
    def setUp(self) -> None:
        self.account: Account = Account("John", 50)
    
    def test_create_account(self):
        expected_acc = {"John": 50}
        self.assertEqual(expected_acc, {self.account.name: self.account.balance})

    def test_deposit(self):
        with mock.patch('logging.info') as mocked_print:
            expected_bal = 100
            depo = 50
            self.account.deposit(depo)
            self.assertEqual(expected_bal, self.account.balance)
            mocked_print.assert_called_with("Deposit successful.")

    def test_withdraw(self):
        with mock.patch('logging.info') as mocked_print:
            expected_bal = 0
            depo = 50
            self.account.withdraw(depo)
            self.assertEqual(expected_bal, self.account.balance)
            mocked_print.assert_any_call("Withdrawal successful.")

    def test_get_balance(self):
        expected_balance = self.account.balance
        self.assertEqual(expected_balance, self.account.get_balance())

class TestValidator(TestCase):
    def setUp(self) -> None:
        self.is_positive = lambda x: x >= 0;
        self.is_odd = lambda x: x % 2 != 0;
        self.input_message: str = "Enter val\n> ";
        self.return_type: type = int
        self.err_message: str = "conditional functions failed"
        self.good_value: int = 9;
        self.bad_value: int = -6;
        self.mocked_input = mock.patch('builtins.input', create=True).start()

    def test_get_and_validate_good_values(self):
        expected: int = 9;
        self.mocked_input.side_effect = [self.good_value]
        val = get_and_validate(self.is_positive, 
                               self.is_odd,
                               input_message=self.input_message,
                               err_message=self.err_message,
                               return_type=self.return_type)
        self.assertEqual(int, type(val))
        self.assertEqual(expected, val)

    def test_get_and_validate_bad_values(self):
        self.mocked_input.side_effect = [self.bad_value]
        with mock.patch('logging.error') as mocked_print:
            self.assertRaises(Exception, 
                              get_and_validate, 
                              self.is_positive, 
                              self.is_odd,
                              input_message=self.input_message, 
                              err_message=self.err_message,
                              return_type=self.return_type)
            mocked_print.assert_called_with("conditional functions failed")



if __name__ == "__main__":
    unittest.main()
