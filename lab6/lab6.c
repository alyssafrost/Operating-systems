#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listing {
  int id, host_id, minimum_nights, number_of_reviews,
      calculated_host_listings_count, availability_365;
  char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
  float latitude, longitude, price;
};

struct listing getfields(char *line) {
  struct listing item;
  item.id = atoi(strtok(line, ","));
  item.host_id = atoi(strtok(NULL, ","));
  item.host_name = strdup(strtok(NULL, ","));
  item.neighbourhood_group = strdup(strtok(NULL, ","));
  item.neighbourhood = strdup(strtok(NULL, ","));
  item.latitude = atof(strtok(NULL, ","));
  item.longitude = atof(strtok(NULL, ","));
  item.room_type = strdup(strtok(NULL, ","));
  item.price = atof(strtok(NULL, ","));
  item.minimum_nights = atoi(strtok(NULL, ","));
  item.number_of_reviews = atoi(strtok(NULL, ","));
  item.calculated_host_listings_count = atoi(strtok(NULL, ","));
  item.availability_365 = atoi(strtok(NULL, ","));

  return item;
}

/*
temp tester to print to terminal
delete this and use writeToFile version for submission
*/
void displayStruct(struct listing item) {
  printf("Host Name : %s\n", item.host_name);
  printf("Price : %f\n", item.price);
}
void writeToFile(char *file_name, int count, struct listing arr[22555]) {
  int i;
  FILE *f = fopen(file_name, "w");

  for (i = 0; i < count; i++) {
    fprintf(f, "ID : %d\n", arr[i].id);
    fprintf(f, "Host ID : %d\n", arr[i].host_id);
    fprintf(f, "Host Name : %s\n", arr[i].host_name);
    fprintf(f, "Neighbourhood Group : %s\n", arr[i].neighbourhood_group);
    fprintf(f, "Neighbourhood : %s\n", arr[i].neighbourhood);
    fprintf(f, "Latitude : %f\n", arr[i].latitude);
    fprintf(f, "Longitude : %f\n", arr[i].longitude);
    fprintf(f, "Room Type : %s\n", arr[i].room_type);
    fprintf(f, "Price : %f\n", arr[i].price);
    fprintf(f, "Minimum Nights : %d\n", arr[i].minimum_nights);
    fprintf(f, "Number of Reviews : %d\n", arr[i].number_of_reviews);
    fprintf(f, "Calculated Host Listings Count : %d\n",
            arr[i].calculated_host_listings_count);
    fprintf(f, "Availability_365 : %d\n\n", arr[i].availability_365);
  }

  fclose(f);
}

static int compare_price(const void *p1, const void *p2) {
  return (((struct listing *)p1)->price - ((struct listing *)p2)->price);
}

static int compare_name(const void *p1, const void *p2) {
  return strcmp(((struct listing *)p1)->host_name,
                ((struct listing *)p2)->host_name);
}

int main(int argc, char *args[]) {
  struct listing list_items[22555];
  char line[1024];
  int i, count;

  FILE *fptr = fopen("mylist.csv", "r");
  if (fptr == NULL) {
    printf("Error reading input file listings.csv\n");
    exit(-1);
  }

  count = 0;
  while (fgets(line, 1024, fptr) != NULL) {
    list_items[count++] = getfields(line);
  }
  fclose(fptr);

  for (i = 0; i < count; i++) {
    qsort(list_items, count, sizeof(struct listing), compare_name);
  }

  for (i = 0; i < count; i++)
    writeToFile("Sorted names.txt", count, list_items);
  printf("\n\n");
  for (i = 0; i < count; i++) {
    qsort(list_items, count, sizeof(struct listing), compare_price);
  }
  
  for (i = 0; i < count; i++)
    writeToFile("Sorted price.txt", count, list_items);

  printf("\n\nSorting and writing to file was successful!\n\n");

  return 0;
}
