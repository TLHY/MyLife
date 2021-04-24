package com.mydb.myapplicationfd;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DatabaseHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME="TagITtest.db";
    private static final int DATABASE_VERSION=8;

    public static final String TABLE_NAME="Sample";
    public static final String ITEM_ID="_id";
    public static final String ITEM_NAME="name";
    public static final String ITEM_IMAGE="image";
    public static final String ITEM_DATE="date";

    public static final String[] ALL_COLUMNS={ITEM_ID,ITEM_NAME,ITEM_IMAGE,ITEM_DATE};//ITEM_DATE

    private static final String CREATE_TABLE="CREATE TABLE "+TABLE_NAME+"("+
            ITEM_ID+" INTEGER PRIMARY KEY AUTOINCREMENT, "+
            ITEM_NAME+" TEXT, "+
            ITEM_IMAGE+" BLOB,"+
            ITEM_DATE+" DATETIME DEFAULT CURRENT_TIMESTAMP "+
            ")";


    public DatabaseHelper(Context context){
        super(context, DATABASE_NAME,null,DATABASE_VERSION);
    }
    public void onCreate(SQLiteDatabase db){
        db.execSQL(CREATE_TABLE);
    }
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion){
        db.execSQL("DROP TABLE IF EXISTS "+TABLE_NAME);
        onCreate(db);
    }
}


