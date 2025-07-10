## 🏦 Banking Management System in C

A console-based banking management system built in the C programming language. This project simulates basic banking operations such as creating accounts, deposits, withdrawals, transfers, and generating transaction statements.

---

### 🔧 Features

* 🆕 Create a new bank account
* 💰 Deposit money to an account
* 💸 Withdraw money from an account
* 🔁 Transfer funds between two accounts
* 📄 View transaction statement
* 🧾 Track all transactions in user-specific files
* 💾 Save and load data using binary file I/O

---

### 🧠 Concepts Used

| Concept               | Description                                   |
| --------------------- | --------------------------------------------- |
| Structures (`struct`) | Represent account details                     |
| File Handling         | Read/write accounts and transactions to files |
| Pointers              | Pass data between functions efficiently       |
| Dynamic File Naming   | User-specific transaction logs                |
| Modular Programming   | Each operation in its own function            |

---

### 📁 Files Created

* **`accounts.dat`** — Binary file storing all account details
* **`account_<number>.txt`** — Individual transaction history per account

---

### 📦 Project Structure

```
banking_system.c
accounts.dat
account_1001.txt
account_1002.txt
...
```

---

### 🔄 ATM Menu

```
====== BANK MENU ======
1. Create Account
2. Deposit
3. Withdraw
4. Transfer
5. Show Statement
6. Exit
=======================
```

---

### 💻 How to Compile & Run

1. Save the code in a file named `banking_system.c`
2. Open terminal / command prompt
3. Compile:

   ```bash
   gcc banking_system.c -o banking
   ```
4. Run:

   ```bash
   ./banking
   ```

---

### 📌 Sample Transaction Log (`account_1001.txt`)

```
Account Created: ₹5000.00
Deposit: ₹2000.00 | New Balance: ₹7000.00
Withdraw: ₹1000.00 | Remaining Balance: ₹6000.00
Transferred ₹500.00 to Acc #1002 | Balance: ₹5500.00
```

---

### 🛠️ Future Improvements

* 🔐 Add login system with passwords
* 🧾 Add mini statement with date/time
* 📊 Admin dashboard for managing all users
* 🌐 GUI version using C++ or Python frontend

---

### 📜 License

This project is free to use for educational and academic purposes.

---


