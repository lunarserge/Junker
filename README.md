# Junker
Helps keep Blocked Senders list in Microsoft Outlook clean.

Microsoft Outlook has a way to specify Blocked Senders list. E-mail from addresses or domain names on the Blocked Senders List is always treated as junk e-mail.
A list entry is specified as either an e-mail address or internet domain name (examples: someone@example.com, @example.com, or example.com).

I decided that if two or more senders from the same domain spam me then the whole domain deserves to be blocked.
Thus, I wrote this little utility to help me keep my Blocked Senders List clean by analyzing my Blocked Senders file (exported from Outlook Junk Email Options).
The utility would point out if several users from the same domain are on the list and offer to remove them in favour of adding one generic domain entry.

Usage:

    Junker.exe Blocked-Senders-File
where Blocked-Senders-File is an export from the Outlook Junk Email Options.

The utility will suggest what should be removed or added to the Blocked Senders List or will report "Blocked-Senders-File is good" in case no change is required.

Since this utility works with Microsoft Outlook it is meant to only be built and used on Windows.

PS. I totally realize C++ isn't the best language for this type of utilities. I did it this way to brush up my C++ skills a little.