"Marks > 75:",
for $x in doc("student.xml")//Student
where $x/Marks/Subject > 75
return concat("SName : ",$x/SName),

"average marks:",
for $x in doc("student.xml")//Student
let $marks := $x/Marks/Subject
let $total := sum(for $m in $marks return xs:integer($m))
let $count := count($marks)
let $avg := $total div $count
return concat("SName : ",$x/SName," | avg : ",$avg),

"total marks:",
for $x in doc("student.xml")//Student
let $total := sum(for $m in $x/Marks/Subject return xs:integer($m))
return concat("SName : ",$x/SName," | total : ",$total),

"Min and Max Marks in a Particular Subject:&#10;",
let $subject := "OS"
let $marks := for $s in doc("student.xml")//Subject[@name = $subject] return xs:integer($s)
let $min := min($marks)
let $max := max($marks)
return concat("Subject: ", $subject, " | Min: ", $min, " | Max: ", $max, "&#10;")
