<!-- Author: Cian Bourke  --> 
<!-- Date: 23/11/2025  --> 
<!-- Programme: This php page will allow users to reserve and view reserved books  -->

<?php

session_start();

include 'Header.php';

// if user is not logged in send to login page
if (!isset($_SESSION['username'])) 
{
    header("Location: Login.php");
    exit();
}

// connect to database
$mysqli = new mysqli("localhost", "root", "", "assignmentproject");

if ($mysqli->connect_error) 
{
    die("Connection failed: " . $mysqli->connect_error);// if connection fails show error
}

$username = $_SESSION['username'];

// if reserve button is pressed
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['isbn'])) 
{
    $isbn = $mysqli->real_escape_string($_POST['isbn']); // get ISBN from post

    // check if user already reserved this book
    $check = $mysqli->query("SELECT 1 FROM reservedbooks WHERE ISBN='$isbn' AND username='$username'");
    if ($check && $check->num_rows === 0) 
    {
        // add reservation to reservedbooks table with current date
        $mysqli->query("INSERT INTO reservedbooks (username, ISBN, reservation_date) 
                        VALUES ('$username', '$isbn', NOW())");

        // update books table to mark book as reserved
        $mysqli->query("UPDATE books SET reserved='Y' WHERE ISBN='$isbn'");
    }
}

// if cancel button is pressed
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['cancel_isbn'])) 
{
    $isbn = $mysqli->real_escape_string($_POST['cancel_isbn']); // get ISBN from post

    // delete reservation for this user only
    $mysqli->query("DELETE FROM reservedbooks WHERE ISBN='$isbn' AND username='$username'");

    // check if anyone else has reserved the book
    $stillReserved = $mysqli->query("SELECT 1 FROM reservedbooks WHERE ISBN='$isbn'");
    if ($stillReserved && $stillReserved->num_rows === 0) 
    {
        // if no one else reserved mark book as available
        $mysqli->query("UPDATE books SET reserved='N' WHERE ISBN='$isbn'");
    }
}

// get all books reserved by this user
$reserved = $mysqli->query("
    SELECT b.ISBN, b.BookTitle, b.Author, b.Edition, b.Book_Year, b.CategoryID, r.reservation_date
    FROM reservedbooks r
    JOIN books b ON r.ISBN = b.ISBN
    WHERE r.username = '$username'
");
?>

<!DOCTYPE html>
<html>
<head>
    <title>My Reserved Books</title>
    <style>
        body 
        {
            background-color: white;
            padding: 20px;
        }
        table 
        {
            width: 100%;
            border-collapse: collapse;
            background: white;
        }
        th, td 
        {
            padding: 10px;
            border: 1px solid black;
        }
        th 
        {
            background: white;
        }
        .btn 
        {
            padding: 6px 12px;
            color: white;
            cursor: pointer;
            text-decoration: none;
            border: 2px solid black;
            display: inline-block;
            color: black;
        }
    </style>
</head>
<body>

<h2>My Reserved Books</h2>

<?php if ($reserved && $reserved->num_rows > 0): ?>
    <table>
        <tr>
            <!-- Table headings for books -->
            <th>ISBN</th>
            <th>Title</th>
            <th>Author</th>
            <th>Edition</th>
            <th>Year</th>
            <th>Category</th>
            <th>Reserved On</th>
            <th>Action</th>
        </tr>

        <?php while ($row = $reserved->fetch_assoc()): ?>
            <tr>
                <!-- Display book details -->
                <td><?php echo htmlspecialchars($row['ISBN']); ?></td>
                <td><?php echo htmlspecialchars($row['BookTitle']); ?></td>
                <td><?php echo htmlspecialchars($row['Author']); ?></td>
                <td><?php echo htmlspecialchars($row['Edition']); ?></td>
                <td><?php echo htmlspecialchars($row['Book_Year']); ?></td>
                <td><?php echo htmlspecialchars($row['CategoryID']); ?></td>
                <td><?php echo date("d-M-Y H:i", strtotime($row['reservation_date'])); ?></td>

                <!-- Cancel reserve book button -->
                <td>
                    <form method="post" action="Reserve.php" style="display:inline;">
                        <input type="hidden" name="cancel_isbn" value="<?php echo $row['ISBN']; ?>">
                        <button type="submit" class="btn">Cancel</button>
                    </form>
                </td>
            </tr>
        <?php endwhile; ?>
    </table>
<?php else: ?>
    <!-- message if no reserved books -->
    <p>You have not reserved any books yet.</p>
<?php endif; ?>

<!-- button tp back to search page -->
<p><a href="Search.php" class="btn">Back to Search</a></p>

</body>
</html>

<?php include 'Footer.php'; ?>
