<!-- Author: Cian Bourke  --> 
<!-- Date: 23/11/2025  --> 
<!-- Programme: This php page will display a header at top the pages  -->
<?php
session_start();

include 'Header.php';


// Connect to your database
$conn = new mysqli("localhost", "root", "", "assignmentproject");

if ($conn->connect_error) 
{
    die("Connection failed: " . $conn->connect_error);
}

$errors = [];

if ($_SERVER["REQUEST_METHOD"] == "POST")// if user submits the registration form run
{
    $username     = trim($_POST['username']);
    $password     = $_POST['password'];
    $confirm      = $_POST['confirm'];
    $email        = trim($_POST['email']);
    $first_name   = trim($_POST['first_name']);
    $second_name  = trim($_POST['second_name']);
    $address_line = trim($_POST['address_line']);
    $address_line2= trim($_POST['address_line2']);
    $city         = trim($_POST['city']);
    $telephone    = trim($_POST['telephone']);
    $mobile       = trim($_POST['mobile']);

    // Check required fields
    if ($username=="" || $password=="" || $confirm=="" || $first_name=="" || $second_name=="" || $address_line=="" || $city=="" || $telephone=="" || $mobile=="") 
    {
        $errors[] = "All fields are required.";
    }

    // Mobile must be 10 digits
    if (!preg_match("/^[0-9]{10}$/", $mobile)) 
    {
        $errors[] = "Mobile must be numeric and 10 digits long.";
    }

    // Password must be 6 characters
    if (strlen($password) != 6) 
    {
        $errors[] = "Password must be exactly 6 characters.";
    }

    // Password confirmation
    if ($password != $confirm) 
    {
        $errors[] = "Passwords dont match.";
    }

    // Check unique username
    $check = $conn->prepare("SELECT Username FROM users WHERE Username=?");

    $check->bind_param("s", $username);

    $check->execute();

    $check->store_result();

    if ($check->num_rows > 0)//check if it matches username in database
    {
        $errors[] = "Username already exists.";
    }

    $check->close();

    // If no errors there are insert user in database
    if (empty($errors)) 
    {
        $stmt = $conn->prepare("INSERT INTO users (Username, Password, Email, First_name, Second_name, address_line, address_line2, city, telephone, mobile) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

        $stmt->bind_param("ssssssssss", $username, $password, $email, $first_name, $second_name, $address_line, $address_line2, $city, $telephone, $mobile);

        if ($stmt->execute()) 
        {
            $_SESSION['username'] = $username;
            header("Location: search.php");
            exit();
        } 
        else 
        {
            $errors[] = "Registration failed.";
        }
        $stmt->close();
    }
}

?>

<!DOCTYPE html>
<html>
<head>
    <title>Register</title>
</head>
<style>

        html,body /* This css cody is for the background */
         {
            margin: 0; 
            padding: 0;
            width: 100%;
            height: 100vh;
            background-image: url("bookImage.webp");
            background-size: cover;
            background-repeat: no-repeat;
            background-position: center center;
            background-attachment: fixed;
            display: flex;
            justify-content: center;
            align-items: center;
        }

        .content /* This centerrs and styles box buttons are in*/
        {
            background-color: white;
            padding: 26px 26px;
            border-radius: 12px;
            text-align: center;
        }

        .box /* This centers and styles the button boxes*/
        {
            border: 2px solid black;
            padding: 10px 20px;
            display: inline-block;
            color: black;
            display: block;
        }

        input 
        {
            width: 180px;
            margin-bottom: 8px;
            align : center;
        }
        

        
    </style>
<body>
    <h2>Register</h2>


    <!-- This will display any errors caught in red to user  --> 
    <?php foreach ($errors as $e) echo "<p style='color:red;'>$e</p>"; ?>

    <form method="post">
        Username: <input type="text" name="username" required><br>
        Password (6 chars): <input type="password" name="password" required><br>
        Confirm Password: <input type="password" name="confirm" required><br>
        Email: <input type="email" name="email"><br>
        First Name: <input type="text" name="first_name" required><br>
        Second Name: <input type="text" name="second_name" required><br>
        Address Line: <input type="text" name="address_line" required><br>
        Address Line 2: <input type="text" name="address_line2"><br>
        City: <input type="text" name="city" required><br>
        Telephone: <input type="text" name="telephone" required><br>
        Mobile (10 digits): <input type="text" name="mobile" required><br>
        <input type="submit" value="Register">
    </form>

    <p><a href="Login.php">Already have an account? Login here</a></p>

</body>
</html>
<?php include 'Footer.php'; ?>
