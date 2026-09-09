<!-- Author: Cian Bourke  --> 
<!-- Date: 23/11/2025  --> 
<!-- Programme: This php page will display a header at top the pages  -->
<!DOCTYPE html>
<html>
<head>
    <title>Cian's Library Database</title>
    <style>
        header 
        {
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            background-color: grey;
            color: black;
            padding: 4px 20px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }

        .box /* This centers and styles the button boxes*/
        {
            border: 2px solid black;
            padding: 5px 5px;
            display: inline-block;
            color: black;
        }

    </style>
</head>
<body>
    <header>
        <div>Cian's Library Database</div>
        <a href="Reserve.php" style="margin-right: 80px;"  class="box">View My Reserved Books</a>
        <a href="Index.php" style="margin-right: 40px;"  class="box">Home</a>
    </header>
    <div class="content">
</body>



