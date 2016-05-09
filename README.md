# FinalProject

php login.php -u joe -p test123 -c addNewUser -nu testuser123 -np test -pl user -rt Paul

	To create a new user, you would need admin username and password
	Then the addNewUser command
	Followed by “-nu” for “new user”
	Specify the name of new user
	-np for “new password”
	Specify the password of new user
	-pl for “privilege level”
	Specify either “user”, “admin”, or “manager”
	-rt for “reports to”
	Specify who that user will report to

php login.php -u Paul -p test123 -c ManagerReportUser

	To get a report of all users that report to their respective manager

php login.php -u joe -p test123 -c DeleteTicket -tid 2

	To delete ticket, specify the command “DeleteTicket” and the TicketID by putting the argument “-tid” and the ID number of the ticket

php login.php -u joe -p test123 -c EditTicket -tid 2 -fn Severity -in 3

	To edit ticket, specify the command “EditTicket” followed by the ‘-tid’ for the ticketID and then the ‘-fn’ argument which means “Fieldname” followed by the “-in” for the input you want to put in

php login.php -u joe -p test123 -c ModifyUserRole -tu testuser123 -pl manager

	To change user role:
	You must be an admin
	Use the “ModifyUserRole” command
	-tu for target user
	-pl for privilege level that you want to assign to user
		admin
		manager
		user 


php login.php -u joe -c CreateTicket -ti testTicket -ct Hardware -sl 3 -des "This is a test Ticket" -st Open

	To create ticket, just put in your username and the “CreateTicket” command followed by:
	-ti for title
	-ct for category
	-sl for severity level
	-des for description
	-st for status


php login.php -u smith -p test -c AssignTicketToSelf -tid 9

	To assign yourself to ticket:
	Use the “AssignTicketToSelf” command
	Specify the ticketID that identifies that ticket


php login.php -u Mohmmad -p test124 -c AssignTicket -tid 11 -tu user23

	For manager to assign ticket to direct report:
	Login as manager
	Use command “AssignTicket”
	Specify the TicketID you want to assign
	Specify the user you want it to assigned to
	IF Ticket is owned by a user that is not direct report to manager:
	Have the manager assign ticket to themselves and then assign it to direct reports

php login.php -u user23 -p test -c AddComment -tid 14 -ac "test Comment"

	To add comment:
	Login as ticketowner or Manager
	Use “AddComment” command
	Specify TicketID
	Specify the “-ac” add comment argument

php login.php -u user23 -p test -c ChangeStatus -tid 10 -st Closed

	To change Status of ticket:
	Use the ChangeStatus command
	Followed by the ticketID and the status argument

php login.php -u user23 -p test -c ViewOwnedTickets

	To view a report of owned tickets:
	Use the ViewOwnedTickets command.

php login.php -u Paul -p test123 -c ManagerTeamReport

	To view report of Team and Tickets owned by team:
	Login as Manager
	Use the ManagerTeamReport command.
