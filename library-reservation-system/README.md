# Library Reservation System

## About
I made this in 2025 as the final project for the second semester of my second year. I really liked how it turned out, so I wanted to highlight it here.

It's a book reservation app where users can log in, sign up, and search through books stored in a database, then choose to reserve one. Building this helped me learn how to connect a database to PHP, and improved my understanding of PHP overall, along with new ways of handling passwords and validating input.

## What it does
- Users can make a new account or log in with an existing one
- Logged in users can search the book database by title, author, or category
- Search results are paginated and show whether a book is available or already reserved
- Users can reserve an available book, or cancel an existing reservation
- A dedicated page shows all books the current user has reserved

## Tech used
- PHP
- MySQL
- HTML/CSS

## Pages
| File | Description |
|---|---|
| `Index.php` | Home page with links to Login and Register
| `Login.php` | Lets a user log in with their registered account
| `Register.php` | Collects user details and creates a new account
| `Search.php` | Search and browse the book database, with pagination
| `Reserve.php` | View, cancel, and manage the current user's reserved books
| `Header.php` | Shared header included on every page
| `Footer.php` | Shared footer included on every page, with logout link

## What I learned
- Connecting PHP to a MySQL database using `mysqli`
- Using prepared statements with bound parameters to help prevent SQL injection
- Managing user sessions so only users that are logged in can access protected pages (Search, Reserve)
- Validating user input on registration
- Building shared header/footer components so every page has consistent navigation and links to previous or home page
- Adding pagination to search results using `LIMIT` and `OFFSET`

## Database structure
The project uses four tables:
- **Users** — stores account details (username, password, email, address, etc.)
- **Category** — stores book categories
- **Books** — stores book details (ISBN, title, author, edition, year, category, reserved status)
- **Reservations** — links users to the books they've reserved, with the reservation date

## Known limitations
These are things that would still need to be fixed if this project were used in the real world:
- Passwords are currently stored in plain text rather than hashed — a real-world version would use `password_hash()` and `password_verify()`
- `Reserve.php` uses `real_escape_string()` for its database queries instead of prepared statements, unlike the other pages

## How to run
1. Install XAMPP or some similar local server with PHP + MySQL
2. Copy this folder into your `htdocs` directory
3. Start Apache and MySQL in the XAMPP control panel
4. Create the database and import the schema in the project portfolio
5. Open the pages in your browser:
  Link for browser: http://localhost/library-reservation-system/Index.php:
