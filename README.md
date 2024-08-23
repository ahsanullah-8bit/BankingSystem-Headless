Note: This project is a year or two old and is not tested since. I'm just preserving my work.

# Building
You need to setup `Connector/C++ 8.0` and a local or a remote **MySQL** server to run this project. It expects the `Connector/C++` to be in the default windows installation dir as `C:\Program Files\MySQL\Connector C++ 8.0`. Otherwise, you can specifically set the `AdditionalLibraryDirectories`, `AdditionalIncludeDirectories` and `AdditionalDependencies` in the configuration settings.

# Interaction of this Project's Classes
	* Banking Class :
		* Account Class :
			* Transaction Class :
	* Database Class :

	1. Banking Class : Man Interface Program handler
		* Sign In()
		* Register()

	2. Account Class :	
		* Database Object
		* Transaction()
		* Update Account()
		* DeleteAccount()
		* Display Data()
	
	3. Transaction	Class :
		* Database Ptr;
		* Contructor(Database Ptr);
		* Deposite()
		* WithDraw()
		* Transfer()

	4. Database Class :
		* addRow()
		* removeRow()
		* updateRowData()
		* displayRowData()
		*
		* transaction();


## Database Schema : bankingsytem_db
	* accounts: id, name, phone, email, cash_amount
	* transactions: acc_id, from, to, amount, time
