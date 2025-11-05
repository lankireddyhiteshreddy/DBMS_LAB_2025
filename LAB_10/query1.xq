for $x in doc("employee.xml")//Employee
where $x/Salary > 30000
return concat("Employee : ",$x/EName," | Salary : ",$x/Salary,"&#10;"),

for $x in doc("employee.xml")//Employee
where starts-with(substring-after($x/EName," "),"S")
return concat("EName : ",$x/EName,"&#10;"),

"Employees in research dept:",
for $x in doc("employee.xml")//Employee
where $x/Dept = "Research"
return concat("EName : ",$x/EName),

"Managers who work more than 8 hours",
for $x in doc("employee.xml")//Employee
where $x/Job = "Manager" and xs:integer($x/WorkingHours) > 8
return concat("EName : ",$x/EName),

"Salary in highest to lowest order:",
for $x in doc("employee.xml")//Employee
order by xs:decimal($x/Salary) descending
return concat("Ename : ",$x/EName," | Salary : ",$x/Salary),

"Employee names in alphabetical order:",
for $x in doc("employee.xml")//Employee
order by $x/EName ascending
return concat("EName : ",$x/EName)
