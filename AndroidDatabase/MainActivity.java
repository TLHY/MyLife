package com.mydb.myapplicationfd;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

import static java.sql.DriverManager.println;

public class MainActivity extends AppCompatActivity {
    TextView textView;
    ImageView imageView;
    ImageView imageView2;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView=findViewById(R.id.textView);
        imageView=findViewById(R.id.imageView);
        imageView2=findViewById(R.id.imageView2);
        Button button=findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                insertItem();
            }
        });
        Button button2=findViewById(R.id.button2);
        button2.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                queryItem();
            }
        });
        Button button3=findViewById(R.id.button3);
        button3.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                updateItem();
            }
        });
        Button button4=findViewById(R.id.button4);
        button4.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                deleteItem();
            }
        });
        Button button5=findViewById(R.id.button5);
        button5.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                addImage();
            }
        });
    }
    public void insertItem(){
        println("Insert Item called");
        String uriString="content://com.mydb.myapplicationfd/TagITtest";
        Uri uri=new Uri.Builder().build().parse(uriString);

        Cursor cursor=getContentResolver().query(uri,null,null,null,null);
        println(uriString);
        println("entering database");
        String[] columns=cursor.getColumnNames();
        println("column count = "+columns.length);
        for(int i=0;i<columns.length;i++){
            println("#"+i+" : "+columns[i]);
        }
        ContentValues values=new ContentValues();
        values.put("name","Example1");
        uri=getContentResolver().insert(uri,values);
    }
    public void insertItem(String name, byte[] image){
        println("Insert Item called");
        String uriString="content://com.mydb.myapplicationfd/TagITtest";
        Uri uri=new Uri.Builder().build().parse(uriString);

        Cursor cursor=getContentResolver().query(uri,null,null,null,null);
        String[] columns=cursor.getColumnNames();
        println("column count = "+columns.length);

        for(int i=0;i<columns.length;i++){
            println("#"+i+" : "+columns[i]);
        }
        ContentValues values=new ContentValues();
        values.put("name",name);
        values.put("image",image);
        uri=getContentResolver().insert(uri,values);
        println("insert result: "+uri.toString());
    }
    public void queryItem(){
        try{
            int index=0;
            String uriString="content://com.mydb.myapplicationfd/TagITtest";
            Uri uri=new Uri.Builder().build().parse(uriString);
            String[] columns=new String[] {"name","image","date"};
            Cursor cursor=getContentResolver().query(uri,columns,null,null,"name ASC");
            println("query result: "+cursor.getCount());
            Handler h=new Handler();
            while(cursor.moveToNext()){
                String name=cursor.getString(cursor.getColumnIndex(columns[0]));
                byte[] images = cursor.getBlob(cursor.getColumnIndex(columns[1]));
                String date=cursor.getString(cursor.getColumnIndex(columns[2]));
                println("#"+index+" = "+name+", "+date);
                if(images!=null){
                    show_image(images);
                }
                index+=1;
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    public void show_image(byte[] images){
        Bitmap oriImg=getImage(images);
        imageView2.setImageBitmap(oriImg);
    }
   public void updateItem(){
        String uriString="content://com.mydb.myapplicationfd/TagITtest";
        Uri uri=new Uri.Builder().build().parse(uriString);

        String selection="_id= ?";
        String [] selectArgs=new String[]{"1"};//input new name
        ContentValues updateValue=new ContentValues();
        updateValue.put("name","NewExample");
        int  count=getContentResolver().update(uri,updateValue,selection,selectArgs);
        println("update result: "+count);
    }
    public void deleteItem(){
        String uriString="content://com.mydb.myapplicationfd/TagITtest";
        Uri uri=new Uri.Builder().build().parse(uriString);

        String selection="name= ?";
        String [] selectArgs=new String[]{"ExampleUpdated"};//input delete name
        int  count=getContentResolver().delete(uri,selection,selectArgs);
        println("delete result: "+count);
    }
    public void addImage(){
        Intent intent=new Intent();
        intent.setType("image/*");
        intent.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(intent,101);
    }
    public void onActivityResult(int requestCode,int resultCode,Intent data){
        super.onActivityResult(requestCode,resultCode,data);
        if(requestCode==101){
            if(resultCode==RESULT_OK){
                Uri fileUri=data.getData();
                ContentResolver resolver=getContentResolver();
                try{
                    InputStream instream=resolver.openInputStream(fileUri);
                    Bitmap imgBitmap= BitmapFactory.decodeStream(instream);
                    insertItem("LOL", getBytes(imgBitmap));
                    imageView.setImageBitmap(imgBitmap);
                    instream.close();
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        }
    }
    public static byte[] getBytes(Bitmap bitmap) {
        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 0, stream);
        return stream.toByteArray();
    }
    public static Bitmap getImage(byte[] image) {
        return BitmapFactory.decodeByteArray(image, 0, image.length);
    }
    public void println(String data){
        textView.append(data+"\n");
    }
}