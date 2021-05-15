
import pymysql

def enrolStudent():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor()
    print("=================================================")
    sql="insert into student (sno,sname,syear,dept) values (%s,%s,%s,%s)"
    v=list(map(str,input("student number, student name, student year, dept: ").split()))
    curs.execute(sql,v)
    conn.commit()
    curs.close()
    conn.close()
def delStudent():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor()
    print("=================================================")
    sno=input("Input Student Number for Deletion: ");
    sql="delete from student where sno= %s"
    curs.execute(sql,sno)
    conn.commit()
    curs.close()
    conn.close()
def viewStudent():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor(pymysql.cursors.DictCursor)
    print("=================================================")
    print("1.View All 2.Search by Sno")
    num=input("Select Option\n")
    if num == "1":
        sql="select * from student order by sno asc"
        curs.execute(sql)
        row=curs.fetchone()
        while row:
            print("Sno: %s, Name: %s, Syear: %s, Dept: %s" %(row['sno'],row['sname'],row['syear'],row['dept']))
            row=curs.fetchone()
    elif num == "2":
        snum=input("Input Student Number: ")
        sql="select * from student where sno = %s"
        curs.execute(sql,snum)
        row=curs.fetchone()
        while row:
            print("Sno: %s, Name: %s, Syear: %s, Dept: %s" %(row['sno'],row['sname'],row['syear'],row['dept']))
            row=curs.fetchone()
    else: print("Incorrect Input!")
    curs.close()
    conn.close()
def enrolCourse():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor()
    print("=================================================")
    sql="insert into course (cno,cname,credit,dept,PRname) values (%s,%s,%s,%s,%s)"
    v=list(map(str,input("course number, course name, course credit, dept, professor name: ").split()))
    curs.execute(sql,v)
    conn.commit()
    curs.close()
    conn.close()
def delCourse():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor()
    print("=================================================")
    cno=input("Input Course Number for Deletion: ");
    sql="delete from course where cno= %s"
    curs.execute(sql,cno)
    conn.commit()
    curs.close()
    conn.close()
def viewCourse():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor(pymysql.cursors.DictCursor)
    print("=================================================")
    print("1.View All 2.Search by Cno")
    num=input("Select Option\n")
    if num == "1":
        sql="select * from course order by cno asc"
        curs.execute(sql)
        row=curs.fetchone()
        while row:
            print("Cno: %s, Name: %s, Credit: %s, Dept: %s, PRname: %s" %(row['cno'],row['cname'],row['credit'],row['dept'],row['PRname']))
            row=curs.fetchone()
    elif num == "2":
        snum=input("Input Course Number: ")
        sql="select * from course where cno = %s"
        curs.execute(sql,snum)
        row=curs.fetchone()
        while row:
            print("Cno: %s, Name: %s, Credit: %s, Dept: %s, PRname: %s" %(row['cno'],row['cname'],row['credit'],row['dept'],row['PRname']))
            row=curs.fetchone()
    else: print("Incorrect Input!")
    curs.close()
    conn.close()
def enrolClass():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor()
    print("=================================================")
    sql="insert into enrollist (sno,cno) values(%s,%s)"
    v=list(map(str,input("student number, course number: ").split()))
    curs.execute(sql,v)
    conn.commit()
    curs.close()
    conn.close()
def cancelClass():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor()
    print("=================================================")
    v=list(map(str,input("student number, course number: ").split()))
    sql="delete from enrollist where SNO= %s AND CNO = %s"
    curs.execute(sql,v)
    conn.commit()
    curs.close()
    conn.close()
def viewClass():
    conn=pymysql.connect(host='localhost',user='root',password='****',db='university2',
                   )
    curs=conn.cursor(pymysql.cursors.DictCursor)
    print("=================================================")
    print("1.View All 2.Search by sno 3.Search by cno\n")
    num=input("Select: ")
    if num == "1":
        sql="select * from enrollist order by SNO asc"
        curs.execute(sql)
        row=curs.fetchone()
        while row:
           print("Sno: %s, Cno: %s" %(row['SNO'],row['CNO']))
           row=curs.fetchone()
    elif num == "2":
        snum=input("Input Student Number: ")
        sql="select * from enrollist where SNO= %s"
        curs.execute(sql,snum)
        row=curs.fetchone()
        while row:
            print("Sno: %s, Cno: %s" %(row['SNO'],row['CNO']))
            row=curs.fetchone()
    elif num == "3":
        cnum=input("Input Course Number: ")
        sql="select * from enrollist where CNO = %s"
        curs.execute(sql,cnum)
        row=curs.fetchone()
        while row:
            print("Sno: %s, Cno: %s" %(row['SNO'],row['CNO']))
            row=curs.fetchone()
    else: print("Incorrect Input!")
    curs.close()
    conn.close()
def studentMenu():
    while(1):
        print("=================================================")
        print("1.Add Student 2.Delete Student 3.View Student 4.Exit\n")
        v=input("Select Menu: ")
        if v=="1":
            enrolStudent()
        elif v=="2":
            delStudent()
        elif v=="3":
            viewStudent()
        elif v=="4":
            break
        else: continue
def courseMenu():
    while(1):
        print("=================================================")
        print("1.Add Course 2.Delete Course 3.View Course 4.Exit\n")
        v=input("Select Menu: ")
        if v=="1":
            enrolCourse()
        elif v=="2":
            delCourse()
        elif v=="3":
            viewCourse()
        elif v=="4":
            break
        else: continue
def enrolMenu():
    while(1):
        print("=================================================")
        print("1.Enroll Class 2.Cancel Class 3.View Class 4.Exit\n")
        v=input("Select Menu: ")
        if v=="1":
            enrolClass()
        elif v=="2":
            cancelClass()
        elif v=="3":
            viewClass()
        elif v=="4":
            break
        else: continue
def main():
    while(1):
        print("=================================================")
        print("1.Student 2.Course 3.ClassEnroll 4.Exit\n")
        v=input("Select Menu: ")
        if v == "1":
            studentMenu()
        elif v == "2":
            courseMenu()
        elif v == "3":
            enrolMenu()
        elif v == "4":
            break
        else: continue
if __name__ == "__main__":
	main()
