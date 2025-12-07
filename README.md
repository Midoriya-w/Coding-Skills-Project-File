# Student Record Management System with RBAC

A robust Command Line Interface (CLI) based Student Record Management System developed in **C**. This project implements **Role-Based Access Control (RBAC)** to manage permissions for different types of users (Admin, Staff, Student, Guest).

## 🚀 Features

- **Role-Based Login System:** Secure login with four distinct access levels.
- **Data Persistence:** All student records and user credentials are stored in text files (`students.txt`, `credentials.txt`).
- **CRUD Operations:** Create, Read, Update, and Delete student records.
- **Search Functionality:** Search by Roll Number or Name.
- **Input Validation:** Prevents duplicate roll numbers.

## 👥 User Roles & Permissions

| Role | Permissions |
| :--- | :--- |
| **ADMIN** | Full Access: Add, View, Search, Update, and Delete records. |
| **STAFF** | Restricted Access: Add, View, and Search records. Cannot Delete or Update. |
| **USER** | Read-Only: Can only view the list of students. |
| **GUEST** | Minimal Access: Can only view the total count of registered students. |

## 🛠️ Tech Stack

- **Language:** C
- **File Handling:** Standard I/O (`stdio.h`)
- **String Manipulation:** `string`

## ⚙️ Installation & Setup

1. **Clone the repository**
   ```bash
   git clone [https://github.com/your-username/student-management-system.git](https://github.com/your-username/student-management-system.git)
   cd student-management-system
