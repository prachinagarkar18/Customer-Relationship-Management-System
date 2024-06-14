#include<stdio.h> // provides basic i/p o/p
#include<stdlib.h> //fh involving memory allocation,proess control,conversions,
#include<string.h> //string fhs
struct node{
    //template for node of ll
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node* next;
};

//global ptrs for customer and admin thrgout the prgm
struct node *headc = NULL, *newnode, *tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *heads;

//options for admin
void adminmenu(){
    printf("\n\t\t\t\t\t\t 1.View total sales\n");
    printf("\n\t\t\t\t\t\t 2.Add new items in the order menu\n");
    printf("\n\t\t\t\t\t\t 3.Delete items from the order menu\n");
    printf("\n\t\t\t\t\t\t 4.Display order menu\n");
    printf("\n\t\t\t\t\t\t 5.Back to Main Menu\n");
    printf("\n\t\t\t\t\t\t Enter Your Choice ---->");
}

// options for customer menu
void customermenu(){
    printf("\n\t\t\t\t\t\t 1.Place your order\n");
    printf("\n\t\t\t\t\t\t 2.View your ordered items\n");
    printf("\n\t\t\t\t\t\t 3.Delete an item from order\n");
    printf("\n\t\t\t\t\t\t 4.Back to Main Menu\n");
    printf("\n\t\t\t\t\t\t Enter Your Choice ---->");
}

//creates a node for admin ll
struct node* createadmin(struct node *head,int data,char foodname[25],float price){
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->price = price;
    newnode->quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    struct node *temp = head;
    if(temp==NULL){
        heada = taila = newnode;
    }else{
        while(temp->next != NULL){
            temp=temp->next;
        }
        temp->next=newnode;
        taila=newnode;
    }
    return heada;
}

//creates a node for customer's ll
struct node* createcustomer(struct node *head,int data,int quantity){
    newnode = (struct node*)malloc(sizeof(struct node));
    struct node *temp1 = heada;
    int flag=0;
    while(temp1!=NULL){
        if(temp1->data == data){
            flag=1;
            break;
        }
        temp1 = temp1->next;
    }
    if(flag==1){
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode->quantity = quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        struct node *temp=head;
        if(temp==NULL)
            headc = tailc = newnode;
        else{
            while(temp->next != NULL)
                temp=temp->next;
            temp->next=newnode;
            tailc=newnode;
        }
    }
    else{
        printf("\n\t\t\t\t\t\t Item not present in the menu\n");
    }
    return headc;
}

//display ll
void displayList(struct node *head){
    struct node *temp1 = head;
    if(temp1==NULL){
        printf("\n\t\t\t\t\t\t List is empty\n\n");
    }else{
        printf("\n");
        while(temp1!=NULL){
            if(temp1->quantity==0)
                printf("\n\t\t\t\t\t\t %d \t %s \t\t %0.2f\n",temp1->data,temp1->foodname,temp1->price);
            else{
                printf("\n\t\t\t\t\t\t %d \t %s \t %d \t\t %0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
            }
                temp1 = temp1->next;
        }
        printf("\n");
    }
}

//maintains the total value of sales done by maintaining another ll which tracks of the total sales made to each customer represented by each node
struct node* totalsales(int data,int quantity){
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag=0;
    struct node *temp1 = heada;
    while(temp1->data!=data){
        temp1 = temp1->next;
    }
    newnode->data = data;
    newnode->quantity=quantity;
    newnode->price = quantity*(temp1->price);
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    struct node *temp = heads;
    if(temp==NULL){
        heads=newnode;
    }else{
        while(temp->next!=NULL){
            if(temp->data==data){
                flag=1;
                break;
            }
            temp=temp->next;
        }
        if(flag==1){
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }else{
            temp->next=newnode;
        }
    }
    return heads;
}

//total sales for each customer
void calculatetotalsales(){
    struct node *temp = headc;
    while(temp!=NULL){
        heads  =totalsales(temp->data,temp->quantity);
        temp=temp->next;
    }
}

//delets data from ll whose head ptr is passed
struct node* delete(int data,struct node *head,struct node *tail){
    if(head==NULL){
        printf("\n\t\t\t\t\t\t List is empty\n");
    }
    else{
        struct node* temp;
        if(data==head->data){
            temp=head;
            head=head->next;
            free(temp);
        }
        else if(data==tail->data){
            temp=tail;
            tail->next = NULL;
            free(temp);
        }
        else{
            temp=head;
            struct node* temp1=temp;
            while(data!=temp->data){
                temp1=temp;
                temp = temp->next;
            }
            temp1->next = temp->next;
            free(temp);
        }
    }
    return head;
}

//delete from adminlist
int deleteadmin(){
    printf("\n\t\t\t Enter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);
    struct node* temp=heada;
    while(temp!=NULL){
        if(temp->data==num){
            heada = delete(num,heada,taila);
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

//delete from customer ll
int deletecustomer(){
    printf("\n\t\t\t Enter serial no. of the food item which is to be deleted:");
    int num;
    scanf("%d",&num);
    struct node* temp=headc;
    while(temp!=NULL){
        if(temp->data==num){
            headc = delete(num,headc,tailc);
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

//total bill ordered by customer
void displaybill(){
    displaybill(headc);
    struct node *temp = headc;
    float total_price=0;
    while(temp!=NULL){
        total_price += (temp->quantity*(temp->price));
        temp=temp->next;
    }
    printf("\n\t\t\t\t\t\t Total price: %0.02f \n",total_price);
}

//delete entire ll
struct node* deleteList(struct node* head){
    if(head==NULL){
        return NULL;
    }
    else{
        struct node* n, *temp=head;
        while(temp!=NULL){
            n = temp->next;
            free(temp);
            temp=n;
        }
        head=NULL;
    }
    return head;
}

// funtionalities for admin interface
void admin(){
    printf("\t\t\t\t\t");
    printf("--------------------------------------------\n");
    printf("\t\t\t\t\t\t\t ADMIN SECTION\n");
    printf("\t\t\t\t\t");
    printf("--------------------------------------------\n");
    while(1){
        adminmenu(); //prints admins funcs
        int opt;
        scanf("%d",&opt);
        if(opt==5){
            break;
        }
        switch(opt){
            case 1:
                displayList(heads);
                break;
            case 2:
                printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
                int num,flag=0;
                char name[50];
                float price;
                scanf("%d",&num);
                struct node *temp = heada;
                while(temp!=NULL){
                    if(temp->data==num){
                        printf("\n\t\t\t\t\t\tFood item already exists!!\n\n");
                        flag=1;
                        break;
                    }
                    temp = temp->next;
                }
                if(flag==1){
                    break;
                }
                printf("\n\t\t\t\t\t\tEnter food item name: ");
                scanf("%s",name);
                printf("\n\t\t\t\t\t\tEnter price: ");
                scanf("%d",&price);
                heada = createadmin(heada,num,name,price);
                printf("\n\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;
            
            case 3:
                if(deleteadmin()){
                    printf("\n\t\t\t\t\t\t### Updated list of food menu ###\n");
                    displayList(heada);
                }
                else{
                    printf("\n\t\t\t\t\t\tFood item with given serial no. doesn't exists! ");
                    break;
                }
            case 4:
                printf("\n\t\t\t\t\t\t ### Order Menu ###\n");
                displayList(heada);
                break;
            default:
                printf("\n\t\t\t\t\t\tWrong Input! Please choose valid option\n");
                break;

        }
    } 
}

void customer(){
    int flag=0,j=1;
    char ch;
    printf("\t\t\t\t\t");
    printf("--------------------------------------------\n");
    printf("\t\t\t\t\t\t\t CUSTOMER SECTION\n");
    printf("\t\t\t\t\t");
    printf("--------------------------------------------\n");
    while(1){
        customermenu();
        int opt;
        scanf("%d",&opt);
        if(opt==5){
            break;
        }
        switch(opt){
            case 1:
                displayList(heada);
                printf("\t\t\t\tEnter number corresponding to the item you want to order:");
                int n;
                scanf("%d",&n);
                printf("\t\t\t\t\t\t\tEnter qunatity:");
                int quantity;
                scanf("%d",&quantity);
                headc = createcustomer(headc,n, quantity);
                break;
            case 2:
                printf("\t\t\t\t\t\t\t ### List of ordered items ###\n");
                displayList(headc);
                break;
            case 3:
                if(deletecustomer()){
                    printf("\t\t\t\t\t\t\t ### Updated list of your ordered food items ###\n");
                    displayList(headc);
                }
                else{
                    printf("\n\t\t\t\t\t\tFood item with given serial no. dosen't exists!!\n");
                }
                break;
            case 4:
                calculatetotalsales();
                printf("\t\t\t\t\t\t\t ### Final Bill ###\n");
                displaybill();
                headc = deleteList(headc);
                printf("\t\t\t\t\t\t\tPress any key to return to main menu: \n");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;
            default:
                printf("\n\t\t\t\t\t\tWrong Input!! Please choose valid option\n");
                break;
        if(flag==1){
            break;
        }
        }
    }
}

//main menu
void mainmenu(){
    printf("\t\t\t\t\t**********************************************\n");
    printf("\t\t\t\t\t\tWELCOME TO RESTAURANT MANAGEMENT\n");
    printf("\t\t\t\t\t**********************************************\n\n");
    printf("\t\t\t\t\t\t1. ADMIN SECTION---> \n");
    printf("\t\t\t\t\t\t2. CUSTOMER SECTION---> \n");
    printf("\t\t\t\t\t\t3. EXIT---> \n\n");
    printf("\t\t\t\t\t\tEnter your choice--->");
}

int main(){
    heada = createadmin(heada, 1 , "Hot&Sour Soup",100);
    heada = createadmin(heada, 2 , "Hot Chocolate",150);
    heada = createadmin(heada, 3 , "Spring Roll",50);
    heada = createadmin(heada, 4 , "Berry1 Mohito",230);
    heada = createadmin(heada, 5 , "Veg Noodles",120);

    while(1){
        mainmenu();
        int choice;
        scanf("%d",&choice);
        if(choice==3){
            printf("\n\n\t\t\t\t\t************Thank You!!************");
            break;
        }
        switch(choice){
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;
            default:
                printf("\n\t\t\t\t\tWrong Input!! Please choose valid option\n");
                break;
        }
    }
}