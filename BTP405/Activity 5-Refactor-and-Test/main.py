from Bank import Bank;
import sys;
def main():
    ac = Bank();
    while True:
        print("\nWelcome to the simple banking system")
        print("1. Create Account")
        print("2. Deposit")
        print("3. Withdraw")
        print("4. View Balance")
        print("5. Exit")
        choice = input("Enter your choice: ")
        
        if choice == '1':
            ac.create_account()
        elif choice == '2':
            ac.deposit()
        elif choice == '3':
            ac.withdraw()
        elif choice == '4':
            ac.view_balance()
        elif choice == '5':
            print("Thank you for using the banking system. Goodbye!")
            sys.exit()
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()