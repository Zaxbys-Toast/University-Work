package Mproject.util;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;

public class UserInfo {
	private Statement userstmt;
	private Statement msgstmt;
	private SqlServerDbAccessor userdb;
	private SqlServerDbAccessor msgdb;

	public UserInfo() {
		userdb = new UserDBA();
		msgdb = new MessageDBA(); 
		
	}


/*
	public static void main(String[] args) {
		SelectTest test = new SelectTest();
		
		String[] cols = {"ID", "Login", "Password"};
		test.selectColumnsFromTable("DL27Login", cols);
	}
*/

	public String getUsername(int userID)
	{
		String query = "SELECT * FROM Test2User WHERE userId = ?;";
		ResultSet result = null;
		String ret = "";

		try {
			userstmt = userdb.getConnection().prepareStatement(query);
			((java.sql.PreparedStatement) userstmt).setString(1, Integer.toString(userID));

			result = ((java.sql.PreparedStatement) userstmt).executeQuery();

			if (result.next()) {
				ret = result.getString("UserName");
			}	
		} catch (SQLException e) { 
			e.printStackTrace();

		} finally {
                    // Close resources to avoid memory leaks
                    try {
                        if (result != null) result.close();
                        if (userstmt != null) userstmt.close();
                        if (userdb.getConnection() != null) userdb.getConnection().close();
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
		return ret;
	}
	
	public int userID(String username) {
		String query = "SELECT * FROM Test2User WHERE UserName = ?;";
		ResultSet result = null;
		int ret = 0;
        
		try {
		    // Prepare the query with the username and password to avoid SQL injection
		    userstmt = userdb.getConnection().prepareStatement(query);
		    ((java.sql.PreparedStatement) userstmt).setString(1, username);
		    
		    result = ((java.sql.PreparedStatement) userstmt).executeQuery();

		    // If result is not null and contains any records, user exists
		    if (result.next()) {
			ret = result.getInt("UserID");
		    }
		} catch (SQLException e) {
		    e.printStackTrace();
		} finally {
		    // Close resources to avoid memory leaks
		    try {
			if (result != null) result.close();
			if (userstmt != null) userstmt.close();
			if (userdb.getConnection() != null) userdb.getConnection().close();
		    } catch (SQLException e) {
			e.printStackTrace();
		    }
		}

		return ret;
	}


	public boolean checkUserExistence(String username, String password) {
        String query = "SELECT * FROM Test2User WHERE UserName = ? AND Password = ?";
        
        ResultSet result = null;
        boolean userExists = false;
	if(username.equals("")) return false;
        
        try {
            // Prepare the query with the username and password to avoid SQL injection
            userstmt = userdb.getConnection().prepareStatement(query);
            ((java.sql.PreparedStatement) userstmt).setString(1, username);
            ((java.sql.PreparedStatement) userstmt).setString(2, password);
            
            result = ((java.sql.PreparedStatement) userstmt).executeQuery();

            // If result is not null and contains any records, user exists
            if (result.next()) {
                userExists = true;
            } 
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            // Close resources to avoid memory leaks
            try {
                if (result != null) result.close();
                if (userstmt != null) userstmt.close();
                if (userdb.getConnection() != null) userdb.getConnection().close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        System.out.println(result);
        return userExists;
    }

	// internal class for db access of user info
	private class UserDBA extends SqlServerDbAccessor {
		public UserDBA() {
			super(); // SqlServerDbAccessor();
			setDbName("test2_MZ");
			connectToDb();
		}
	}

	// internal class for db access of messages
	private class MessageDBA extends SqlServerDbAccessor {
		// TODO: this
		public MessageDBA() {
			super();
		}
	}

}
