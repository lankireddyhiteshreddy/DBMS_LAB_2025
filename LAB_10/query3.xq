"Price < 5000",
for $x in doc("flight.xml")//Flight
where $x/Price < 5000
return concat("FlNo : ",$x/FlNo," | FlName : ",$x/FlName," | Price : ",$x/Price),

for $x in doc("flight.xml")//Flight
where $x/DateDeparts = "2020-12-04"
return concat("Departs time : ",$x/TimeDeparts," | From : ",$x/From),

let $pilot := "Rahul Mehta"
return(
    concat("Flights handled by ",$pilot),
    for $x in doc("flight.xml")//Flight
    where $x/PilotName = $pilot
    return concat("FlightName : ",$x/FlName)
),

let $flight := 104
let $date := "2020-11-25"
let $x := doc("flight.xml")//Flight
let $count := count(for $m in $x where $m/FlNo = $flight and $m/DateDeparts = $date return $m)
return concat("Number of flight journeys for Flight ",$flight," on ",$date," is :",$count),

let $date := "2020-11-25"
let $flight := 104
for $x in doc("flight.xml")//Flight
where $x/DateDeparts = $date and $x/FlNo = $flight
return concat("FlNo : ",$x/FlNo," | date : ",$x/DateDeparts," | arrival time : ",$x/TimeArrives)
