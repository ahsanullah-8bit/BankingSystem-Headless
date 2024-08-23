# Interaction of this Project Class
	*	Banking Class :
		*	Account Class :
			*	Transaction Class :
	* Database Class :

	1. Banking Class :	Man Interface Program handler
			*	Sign In()
			*	Register()

	2. Account Class :	
			*	Database Object
			*	Transaction()
			*	Update Account()
			*	Delete	Account()
			*	Display Data()
	
	3. Transaction	Class :
			*	Database Ptr;
			*	Contructor(Database Ptr);
			*	Deposite()
			*	WithDraw()
			*	Transfer()

	4.	Database Class :
			*	addRow()
			*	removeRow()
			*	updateRowData()
			*	displayRowData()
			*
			*	transaction();


# Database Schema : bankingsytem_db
		*	accounts: id, name, phone, email, cash_amount
		*	transactions: acc_id, from, to, amount, time

	
			
# Entities
* Bank
* Account
* Database
* Transaction

### Their Interaction
1. **Bank**
```
- Database Class

+ Sign in
+ Sign up
```

2. **Account**
```
- Database Ptr

+ Display Data()
+ Update Account()
+ Delete Account()
+ Transaction()
```

3. **Database**
```
+ addAccount()
+ checkAccount()
+ deleteAccount()
+ updateAccount()
+ getAccountInfo()
+ getAllAccounts()
+ transactionDeposite()
+ transactionWithDraw()
+ transactionTransfer()
```

4. **Transaction**
```
- Database Ptr;

+ Contructor(Database Ptr);
+ Deposite()
+ WithDraw()
+ Transfer()
```
