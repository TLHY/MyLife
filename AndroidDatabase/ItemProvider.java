package com.mydb.myapplicationfd;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;

import androidx.annotation.Nullable;

public class ItemProvider extends ContentProvider {
    private static final String AUTHORITY="com.mydb.myapplicationfd";
    private static final String BASE_PATH="TagITtest";
    private static final Uri CONTENT_URI=Uri.parse("content://"+AUTHORITY+"/"+BASE_PATH);

    private static final int ITEMS=1;
    private static final int ITEMS_ID=2;
    private static final UriMatcher uriMatcher=new UriMatcher(UriMatcher.NO_MATCH);
    static{
        uriMatcher.addURI(AUTHORITY,BASE_PATH,ITEMS);
        uriMatcher.addURI(AUTHORITY,BASE_PATH+"/#",ITEMS_ID);
    }
    private SQLiteDatabase database;


    @Override
    public boolean onCreate() {
        DatabaseHelper helper=new DatabaseHelper(getContext());
        database=helper.getWritableDatabase();
        return true;
    }
    @Nullable
    @Override
    public Cursor query(Uri uri,String[] strings, String sel,String[] selArgs, String sortOrder) {
        Cursor cursor;
        System.out.print(uriMatcher.match(uri));
        switch(uriMatcher.match(uri)){
            case ITEMS:
                cursor=database.query(DatabaseHelper.TABLE_NAME,
                        DatabaseHelper.ALL_COLUMNS,
                        sel,null,null,null,DatabaseHelper.ITEM_NAME+" ASC");
                break;
            default:
                throw new IllegalArgumentException("Unknown URI"+uri);
        }
        cursor.setNotificationUri(getContext().getContentResolver(),uri);

        return cursor;
    }

    @Nullable
    @Override
    public String getType(Uri uri) {
        switch(uriMatcher.match(uri)){
            case ITEMS:
                return "vnd.android.cursor.dir/items";
            default:
                throw new IllegalArgumentException("Unknown URI"+uri);
        }
    }

    @Nullable
    @Override
    public Uri insert(Uri uri, ContentValues values) {
        long id=database.insert(DatabaseHelper.TABLE_NAME,null,values);
        if(id>0){
            Uri _uri= ContentUris.withAppendedId(CONTENT_URI,id);
            getContext().getContentResolver().notifyChange(_uri,null);
            return _uri;
        }
        throw new SQLException("Addition Failed->URI : "+uri);
    }

    @Override
    public int delete(Uri uri, String sel, String[] selArgs) {
        int count=0;
        switch (uriMatcher.match(uri)){
            case ITEMS:
                count=database.delete(DatabaseHelper.TABLE_NAME,sel,selArgs);
                break;
            default:
                throw new IllegalArgumentException("Unknown URI"+uri);
        }
        getContext().getContentResolver().notifyChange(uri,null);
        return count;
    }

    @Override
    public int update( Uri uri, ContentValues values, String sel,String[] selArgs) {
        int count=0;
        switch (uriMatcher.match(uri)){
            case ITEMS:
                count=database.update(DatabaseHelper.TABLE_NAME,values,sel,selArgs);
                break;
            default:
                throw new IllegalArgumentException("Unknown URI"+uri);
        }
        getContext().getContentResolver().notifyChange(uri,null);
        return count;
    }

}
