#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct node {
    char name[128];
    struct node *next; 
};

void list_insert(const char *name, struct node **head) {
     struct node *newnode = malloc(sizeof(struct node));
     strncpy(newnode->name, name, 127);

     newnode->next = *head;
     *head = newnode;
}

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}


void list_print_matches(const char *name, const struct node *head) {  
	int stringLength = strlen(name);
	while (head!=NULL) { 
		if (strncasecmp(name, head->name, stringLength)==0) {
			printf("%s\n",head->name);
		}
		head = head->next;
	}
    
}


int list_delete(const char *name, struct node **head) {
	int stringLength = strlen(name);	
	struct node *new = (struct node*)malloc(sizeof(struct node));

	new->next = *head;
	if (strncasecmp(name,new->next->name, stringLength)==0){ //check first
		*head = new->next->next;
		free(new);
		return 1;

	}
	while (new->next->next!=NULL) {
		if (strncasecmp(name,new->next->next->name,stringLength)==0){
			new->next->next = new->next->next->next;
			free(new);	
			return 1;
		}
		new->next = new->next->next;
	}

	free(new);
	return 0;
}

void list_append(const char *name, struct node **head) {
	struct node *new = (struct node*)malloc(sizeof(struct node));
	struct node *new2 = (struct node*)malloc(sizeof(struct node));
	new2 = *head;
	strcpy(new->name,name);
	new->next=NULL;
	while(new2->next!=NULL) {
		new2=new2->next;
	}


	new2->next=new;
	printf("%s\n","new2->next:");
	printf("%s\n",new2->next->name);
	new2->next->next=NULL;
	//works if I don't free malloc
	//free malloc
	//free(new2);
	//free(new);

}

void list_reverse(struct node **head) {
	struct node *new = (struct node*)malloc(sizeof(struct node));
	struct node *nullNode = (struct node*)malloc(sizeof(struct node));
	new=NULL;
	nullNode= *head;
	list_insert(nullNode->name,&new);
	while(nullNode->next!=NULL) {
		list_insert(nullNode->next->name,&new);
		nullNode->next = nullNode->next->next;
	}

	
	*head=new;
	free(new);


}

void list_sort(struct node **head) {
	struct node *new = (struct node*)malloc(sizeof(struct node));
	new=*head;
	struct node *current = (struct node*)malloc(sizeof(struct node));;
	struct node *following = (struct node*)malloc(sizeof(struct node));;
	struct node *prev = (struct node*)malloc(sizeof(struct node));;
	struct node *temp = (struct node*)malloc(sizeof(struct node));;
	temp = NULL;
	int switch2 = 1;
	while (switch2) {
		switch2 = 0;
		current=new;
		following = current->next;
		prev = NULL;
		while (following!=NULL){
			if (strcmp(current->name, following->name)>0) {	 //make switch
				switch2=1;   //do loop again
				//if currently at head of list
				if (current==new) {
					new = following;
					temp = following->next;
					following->next = current;
					current->next=temp;
					current = new;

				}
				else {
					prev->next = current->next;
					current->next = following->next;
					following->next = current;
					current = following;
				}
			}
			prev = current;
			current = current->next;
			following = current->next;
		}
	}
	*head=new;

}

void printlist(struct node **head) {
	struct node *new = (struct node*)malloc(sizeof(struct node));	
	new=*head;
	while(new!=NULL) {
		printf("%s\n",new->name);
		new=new->next;
	}
	free(new);
}

int main(int argc, char **argv) {
    char buffer[128];

    struct node *head = NULL;

    printf("Next string to add: ");
    fflush(stdout);
    while (fgets(buffer, 128, stdin) != NULL) {

        list_insert(buffer, &head);

        printf("Next string to add: ");
        fflush(stdout);
    }
    printf("%s\n","\n");
    list_print_matches("test", head);	//works
    printf("%s\n","original list:");
    printlist(&head);
    //list_append("hi", &head);		//memory allocation may be off
    //list_delete("test", &head);	//works
   // list_reverse(&head);	//works

    list_sort(&head);	//works
    printf("%s\n","new list:");
    printlist(&head);
    return 0;
}
