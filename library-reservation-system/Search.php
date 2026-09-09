<!-- Author: Cian Bourke  --> 
<!-- Date: 20/11/2025  --> 
<!-- Programme: This php page will allow users to search library database  -->

<?php
session_start();

include 'Header.php';//adds header

$mysqli = new mysqli("localhost", "root", "", "assignmentproject");

// check if it doesnt
if ($mysqli->connect_error) 
{
    die("Database connection failed."); // if it doesnt stop and display message
}

// Logout user and send to homepage
if (isset($_GET['logout'])) 
{
    session_destroy();
    header("Location: Index.php");
    exit();
}

// if thre isnt a registered user bring to home page
if (!isset($_SESSION['username'])) 
{
    header("Location: Login.php");
    exit();
}

// get the CategoryID, CategoryDescription from the database?
$catQuery = $mysqli->query("SELECT CategoryID, CategoryDescription FROM category");

// Get the title name User input
$title    = trim($_GET['title'] ?? '');
$author   = trim($_GET['author'] ?? '');
$category = trim($_GET['category'] ?? '');

// Pages created
$rows_per_page = 5;

// Get current page 1 from query
$page = max(1, intval($_GET['page'] ?? 1));

// calculates the row number to fetch from the database
$offset = ($page - 1) * $rows_per_page;

// Get all books from table with category description
$sql = "SELECT SQL_CALC_FOUND_ROWS books.*, category.CategoryDescription
        FROM books
        JOIN category ON books.CategoryID = category.CategoryID
        WHERE 1=1";

// Array to store the user’s searches and inputs
$params = [];

// empty string to hold types
$types  = "";

// If a title is entered to search
if ($title !== '') {
    // Adds a search condition to the sql query
    $sql .= " AND BookTitle LIKE ?";
    // Adds users search word into the list of parameters
    $params[] = "%$title%";
    // Add string to types
    $types .= "s";
}

// If an author name is entered
if ($author !== '') {
    $sql .= " AND Author LIKE ?";
    $params[] = "%$author%";  // Adds users search word into the list of parameters
    $types .= "s";
}

// If a category was chosen
if ($category !== '') {
    $sql .= " AND books.CategoryID = ?";
    $params[] = $category;
    $types .= "s";
}

// Add pagination (LIMIT, OFFSET)
$sql .= " LIMIT $rows_per_page OFFSET $offset";

// get statement query ready to use
$stmt = $mysqli->prepare($sql);

// bind parameters
if (!empty($params)) {
    $stmt->bind_param($types, ...$params);
}

$stmt->execute();

// Get the result
$result = $stmt->get_result();

// Count total rows for pagination
$total_rows = $mysqli->query("SELECT FOUND_ROWS() AS total")->fetch_assoc()['total'];
$total_pages = ceil($total_rows / $rows_per_page);
?>

<!DOCTYPE html>
<html>
<head>
    <title>Search Books</title>
    <style>
        body 
        {
            background-color: white;
            padding: 20px;
        }
        .search-box 
        {
            background: white;
            padding: 20px;
            border-radius: 10px;
            margin-bottom: 20px;
        }
        
        table 
        {
            width: 100%;
            border-collapse: collapse;
            background: white;
        }

        th, td {
            padding: 10px;
            border: 1px solid black;
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

<!-- search table  -->
<div class="search-box">
    <h2>Search for a Book</h2>

    <form method="get">

        Title: <!-- user title input -->
        <input type="text" name="title" value="<?php echo htmlspecialchars($title); ?>">
        <br><br>

        Author: <!-- user Author input -->
        <input type="text" name="author" value="<?php echo htmlspecialchars($author); ?>">
        <br><br>

        <!-- the category dropdown menu -->
        Category:
        <select name="category">
            <option value="">-- Category Selection --</option>

            <?php while ($cat = $catQuery->fetch_assoc()): ?> <!-- category options -->
                <option value="<?php echo $cat['CategoryID']; ?>"
                    <?php if ($category === $cat['CategoryID']) echo 'selected'; ?>>
                    <?php echo htmlspecialchars($cat['CategoryDescription']); ?>
                </option>
            <?php endwhile; ?>
        </select>

        <br><br>

        <!-- button to submit -->
        <button type="submit" class="btn">Search</button>
    </form>
</div>

<h3>Search Results</h3>

<!-- Page search links -->
<div style="margin-bottom: 10px;">
    <?php for ($i = 1; $i <= $total_pages; $i++): ?>

        <?php if ($i == $page): ?> <!-- Current page number-->
            <strong><?php echo $i; ?></strong>

        <?php else: ?>
            <!-- Links to the other pages -->
            <a class="btn"
               href="Search.php?page=<?php echo $i; ?>&title=<?php echo urlencode($title); ?>&author=<?php echo urlencode($author); ?>
               &category=<?php echo urlencode($category); ?>">
               <?php echo $i; ?>
            </a>
        <?php endif; ?>

    <?php endfor; ?>
</div>

<!-- search results table -->
<table>
    <tr>
        <!--  headings for the table -->
        <th>ISBN</th>
        <th>Title</th>
        <th>Author</th>
        <th>Edition</th>
        <th>Year</th>
        <th>Category</th>
        <th>Status</th>
        <th>Action</th>
    </tr>

    <?php while ($row = $result->fetch_assoc()): ?>
        <tr>
            <!-- Display book details -->
            <td><?php echo htmlspecialchars($row['ISBN']); ?></td>
            <td><?php echo htmlspecialchars($row['BookTitle']); ?></td>
            <td><?php echo htmlspecialchars($row['Author']); ?></td>
            <td><?php echo htmlspecialchars($row['Edition']); ?></td>
            <td><?php echo htmlspecialchars($row['Book_Year']); ?></td>
            <td><?php echo htmlspecialchars($row['CategoryDescription']); ?></td>

            <!-- Show reserved status -->
            <td><?php echo $row['reserved'] === 'Y' ? "Reserved" : "Available"; ?></td>

            <td>
                <?php if ($row['reserved'] === 'Y'): ?> <!-- If reserved display -->
                    <em>Not available</em>
                <?php else: ?>

                    <!-- If available allow to click reserve button -->
                    <form method="post" action="Reserve.php">
                        <input type="hidden" name="isbn" value="<?php echo $row['ISBN']; ?>">
                        <button type="submit" class="btn">Reserve</button>
                    </form>

                <?php endif; ?>
            </td>
        </tr>
    <?php endwhile; ?>

</table>

</body>
</html>
<?php include 'Footer.php'; ?>
