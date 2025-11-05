for $x in doc("employee2.xml")//Employee
where $x/Dept = "Human Resources"
return concat("Ename : ",$x/EName," | Dept : ",$x/Dept),

let $project := "Alpha"
for $x in doc("employee2.xml")//Employee
where $x/Project = $project and $x/Salary > 50000
return concat("Ename : ",$x/EName),

let $dept := "Human Resources"
let $x := doc("employee2.xml")//Employee
let $total := sum(for $m in $x where $m/Dept = $dept return $m/Salary)
return concat("Sum of salary in ",$dept," is : ",$total),

let $dept := "Human Resources"
let $x := doc("employee2.xml")//Employee
let $count := count(for $m in $x where $m/Dept = $dept return $m)
return concat("Number of employees working in ",$dept," is : ",$count),

let $dept := "Human Resources"
let $x := doc("employee2.xml")//Employee
let $max := max(for $m in $x where $m/Dept = $dept and $m/Job = "Manager" return $m/Salary)
return concat("Highest salary of a manager working in ",$dept," is : ",$max)

