#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct //创建结构体
{
	int id;             // 学号
	char name[100];    // 姓名
	float score;      // 成绩
}
student;
student stu[100];
int studentCount = 0; //构建结构体
int getIntInput()
{
	char buffer[100];
	fgets(buffer, sizeof(buffer), stdin);
	return atoi(buffer);
}
float getFloatInput()
{
	char buffer[100];
	fgets(buffer, sizeof(buffer), stdin);
	return atof(buffer);
}

//函数声明部分
void loadFromFile()
{
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL)
	{
		printf("无法读取文件\n");
		return;
	}
	char line[256];
	studentCount = 0;
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (sscanf(line, "%d %99s %f", &stu[studentCount].id, stu[studentCount].name, &stu[studentCount].score) == 3)
		{
			studentCount++;
		}
	}
	fclose(fp);
	printf("成功从文件加载了 %d 条学生记录\n", studentCount);

}
//读取文件函数
void saveToFile()
{
	FILE* fp = fopen("student.txt", "w");
	if (fp == NULL)
	{
		printf("无法打开文件进行写入！\n");
		return;
	}
	for (int i = 0; i < studentCount; i++)
	{
		fprintf(fp, "%d %s %f\n", stu[i].id, stu[i].name, stu[i].score);
	}
	fclose(fp);
	printf("数据已成功保存到文件！\n");
}
//保存数据函数
void sortStudents()
{
	for (int i = 0; i < studentCount; i++)
	{
		for (int j = i; j < studentCount; j++)
		{
			if (stu[i].score > stu[j].score)
			{
				student temp = stu[i];
				stu[i] = stu[j];
				stu[j] = temp;
			}
		}
	}
	for (int i = 0; i < studentCount; i++)
	{
		printf("第%d学生：%s，当前学号；%d,当前成绩：%.1f\n", i, stu[i].name, stu[i].id, stu[i].score);
	}
}
//成绩顺序排列函数
void deleteStudent()
{
	char name[100] = { 0 };
	printf("请输入要删除的学生姓名：");
	fgets(name, sizeof(name), stdin);
	if (strlen(name) > 0 && name[strlen(name) - 1] == '\n')
		name[strlen(name) - 1] = '\0';
	for (int i = 0; i < studentCount; i++)
	{
		if (strcmp(name, stu[i].name) == 0)
		{
			printf("学生：%s，学号；%d,成绩：%.1f\n", stu[i].name, stu[i].id, stu[i].score);
			printf("是否确认删除(是请回复1)\n");
			int a = getIntInput();
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			if (a == 1)
			{
				for (int j = i; j < studentCount; j++)
				{
					stu[j] = stu[j + 1];
				}
				printf("删除成功！\n");
				studentCount--;
				return;
			}
			else
			{
				printf("已取消删除操作！\n");
				return;
			}
		}
	}
	printf("未找到该学生！\n");
	return;
}
//删除学生函数
void modifyStudent()
{
	char name[100] = { 0 };
	printf("请输入要修改的学生姓名：");
	fgets(name, sizeof(name), stdin);
	if (strlen(name) > 0 && name[strlen(name) - 1] == '\n')
		name[strlen(name) - 1] = '\0';
	for (int i = 0; i < studentCount; i++)
	{
		if (strcmp(name, stu[i].name) == 0)
		{
			printf("找到学生：%s，当前学号；%d,当前成绩：%.1f\n", stu[i].name, stu[i].id, stu[i].score);
			printf("请输入新的学生信息：\n");
			printf("学号:");
			stu[i].id = getIntInput();
			printf("成绩:");
			stu[i].score = getFloatInput();
			printf("修改成功，学生：%s，新学号；%d,新成绩：%.1f\n", stu[i].name, stu[i].id, stu[i].score);
			return;
		}
	}
	printf("未找到该学生！\n");
	return;
}
//修改学生函数
void findStudentByName()
{
	char name[100];
	printf("请输入要查找的学生姓名：");
	fgets(name, sizeof(name), stdin);
	if (strlen(name) > 0 && name[strlen(name) - 1] == '\n')
		name[strlen(name) - 1] = '\0';
	for (int i = 0; i < studentCount; i++)
	{
		if (strcmp(name, stu[i].name) == 0)
		{
			printf("学号：%d  姓名：%s  成绩：%f\n", stu[i].id, stu[i].name, stu[i].score);
			return;
		}
	}
	printf("未找到该学生！\n");
	return;
}
//查找学生函数
void showAllstudents()
{
	for (int i = 0; i < studentCount; i++)
	{
		printf("学号：%d  姓名：%s  成绩：%f\n", stu[i].id, stu[i].name, stu[i].score);
	}
}
//显示所有学生函数
void addStudent()
{
	printf("请输入要加入的学生数量：");
	int n = getIntInput();
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	for (int i = 1; i <= n; i++)
	{
		printf("请输入第%d个学生的信息：\n", i);
		printf("学号：");
		stu[studentCount].id = getIntInput();
		printf("姓名：");
		fgets(stu[studentCount].name, sizeof(stu[studentCount].name), stdin);
		if (strlen(stu[studentCount].name) > 0 && stu[studentCount].name[strlen(stu[studentCount].name) - 1] == '\n')
			stu[studentCount].name[strlen(stu[studentCount].name) - 1] = '\0';
		printf("成绩：");
		stu[studentCount].score = getFloatInput();
		printf("学生信息添加成功！\n");
		studentCount++;
	}
}
//添加学生函数
void showMenu()
{
	printf("=====================================\n");
	printf("     学生信息管理系统\n");
	printf("=====================================\n");
	printf("1. 添加学生信息\n");
	printf("2. 显示所有学生\n");
	printf("3. 查找学生（按姓名）\n");
	printf("4. 修改学生信息\n");
	printf("5. 删除学生信息\n");
	printf("6. 按成绩排序\n");
	printf("7. 保存数据到文件\n");
	printf("8. 从文件读取数据\n");
	printf("0. 退出系统\n");
	printf("=====================================\n");
	printf("*******************************\n");
	printf("请输入你的选择：\n");
	//显示主界面

	int choice = getIntInput();
	switch (choice)
	{
	case 1:addStudent(); break;
	case 2:showAllstudents(); break;
	case 3:findStudentByName(); break;
	case 4:modifyStudent();; break;
	case 5: deleteStudent(); break;
	case 6: sortStudents(); break;
	case 7: saveToFile(); break;
	case 8: loadFromFile(); break;
	case 0: exit(0); break;
	}
}
//开始菜单函数	
int main()
{
	loadFromFile();
	while (1)
	{
		printf("\n");
		showMenu();
	}
	saveToFile();
	return 0;
}