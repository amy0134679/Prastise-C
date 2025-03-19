#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 128

typedef struct dimensions
{
  // This struct stores the dimensions of an object.
  // The fields should be self explanatory. The units
  // don't matter here, but say they are meters and kgs.
  float height;
  float depth;
  float width;
  float weight;
} Dimensions;

typedef struct furniture
{
  // This struct stored information about a piece of
  // furniture. Note the nested struct containing the
  // information on the furniture dimensions.
  char name[MAX_STRING_LEN];
  char material[MAX_STRING_LEN];
  float price;
  Dimensions dimensions;
} Furniture;

///////////////////////////////////////////////////////////////////////////////

int find_material(Furniture catalog[], int catalog_size, char *material,
                  Furniture *results[])
{
  /**
   * Given an array (with the size) of furniture items (a catalog), and a
   * string with the name of a material, find all the furniture items in the
   * catalog with the given material. For each matching item, add a pointer to
   * it to the results array (an array of pointers). The order of insertion
   * to `results` must be the same as the order in which the items appear in
   * the catalog. Assume `results` has enough space.
   *
   * Additionally, return the number of matches found.
   */
  int num_matches = 0;

  for (int i = 0; i < catalog_size; i++)
  {
    if (strcmp(catalog[i].material, material) == 0)
    {
      results[num_matches] = &catalog[i];
      num_matches++;
    }
  }

  return num_matches; 
}

int find_price(Furniture catalog[], int catalog_size, float min_price,
               float max_price, Furniture *results[])
{
  /**
   * Similar to the previous function, this time find all the items in the
   * catalog that are within the given price range (inclusive). The order of
   * insertion to `results` must be the same as the order in which the items
   * appear in the catalog. Assume `results` has enough space.
   *
   * Additionally, return the number of matches found.
   */

  int num_matches = 0;

for (int i = 0; i < catalog_size; i++)
{
  if (catalog[i].price >= min_price && catalog[i].price <= max_price)
  {
    results[num_matches] = &catalog[i];
    num_matches++;
  }
}

  return num_matches; 
}

char *biggest_ripoff_name(Furniture catalog[], int catalog_size)
{
  /**
   * We all know that the bigger an item is (more volume), the better it is!
   * (Maybe not, but let's assume that is the case). The biggest ripoff would
   * be the item that costs the *most* amount of money per unit volume. Assume
   * that it is unique, and return it's name.
   */
  char *biggest_ripoff = NULL;
  float worst_ppu = 0.0;

  for (int i = 0; i < catalog_size; i++)
  {
        float volume = catalog[i].dimensions.height *
                   catalog[i].dimensions.depth *
                   catalog[i].dimensions.width;

    float price_per_unit = catalog[i].price / volume;

    if (price_per_unit > worst_ppu)
    {
      worst_ppu = price_per_unit;
      biggest_ripoff = catalog[i].name;
    }
  }

  return biggest_ripoff; 
}

Furniture *update_material(Furniture catalog[], int catalog_size, char *name,
                           char *new_material)
{
  /**
   * Given the furniture catalog, the (unique) name of an item, and a new
   * material name, update the material of the furniture item in the catalog
   * with the given name. Returns a pointer to the updated item.
   *
   * If no item exists in the catalog with the given name, don't change
   * anything and return NULL.
   */

  for (int i = 0; i < catalog_size; i++)
  {
    if (strcmp(catalog[i].name, name) == 0)
    {
      strcpy(catalog[i].material, new_material);
      return &catalog[i];
    }
  }
  return NULL; // Return NULL if the item is not found
}

Furniture *update_dimensions(Furniture catalog[], int catalog_size, char *name,
                             Dimensions *new_dimensions)
{
  /**
   * Given the furniture catalog, the (unique) name of an item, and a
   * *pointer* to a new dimensions struct, update the dimensions of the
   * furniture item in the catalog with the given name. Returns a pointer
   * to the updated item.
   *
   * If no item exists in the catalog with the given name, don't change
   * anything and return NULL.
   */

  for (int i = 0; i < catalog_size; i++)
  {
    if (strcmp(catalog[i].name, name) == 0)
    {
      catalog[i].dimensions = *new_dimensions;
      return &catalog[i];
    }
  }
  return NULL; // Return NULL if the item is not found
}


///////////////////////////////////////////////////////////////////////////////

#ifndef __testing__ // You know the drill; don't remove this.

// However, Feel free to change the line below to add more tests.
#define CATALOG_SIZE 10

int main()
{

  // Defining and array of furniture items. Note that when initializing a
  // a struct (or an array), we can use the { ... } shorthand for them!
  Furniture catalog[CATALOG_SIZE] = {
      //                                       |-------- Dimensions ------------|
      //       name          material    price  height    depth    width  weight
      {"Docksta table", "Wood", 49.99, {2, 1, 1, 10}},
      {"Ektorp sofa", "Leather", 99.99, {2, 5, 1, 100}},
      {"Poang armchair", "Plastic", 24.95, {1, 0.5, 0.5, 4}},
      {"Kallax shelves", "Wood", 149.99, {2, 1, 0.3, 70}},
      {"Flaggskepp lamp", "Metal", 17.99, {0.1, 0.1, 0.1, 1}},
      {"Balkarp sofa", "Leather", 120.00, {0.5, 2, 0.5, 50}},
      {"Jonaxel basket", "Metal", 69.99, {2, 1, 1, 10}},
      {"Nordli bed", "Wood", 339.00, {0.2, 2, 1, 20}},
      {"Renberget chair", "Plastic", 59.99, {1, 0.5, 0.5, 9}},
      {"Kolbjorn cabinet", "Metal", 99.00, {0.8, 0.4, 0.8, 17}},
  };

  // Let's create an array to store the results and the number of results.
  // At most, the number of matches is the same as the size of the array.
  Furniture *results[CATALOG_SIZE];
  int results_n;

  /***************************************************************************/
  /*                            Find material                                */
  /***************************************************************************/

  results_n = find_material(catalog, CATALOG_SIZE, "Wood", results);

  // To make sure our search was done correctly, we will print the results
  printf("Found %d items made of Wood:\n", results_n);
  for (int i = 0; i < results_n; i++)
  {
    printf("Result %d: %s\n", i + 1, results[i]->name);
  }

  /***************************************************************************/
  /*                            Find Price                                   */
  /***************************************************************************/

  results_n = find_price(catalog, CATALOG_SIZE, 0.0, 50.0, results);

  // To make sure our search was done correctly, we will print the results
  printf("\nFound %d items between $0 and $50 (inclusive):\n", results_n);
  for (int i = 0; i < results_n; i++)
  {
    printf("Result %d: %s, $%f\n", i + 1, results[i]->name, results[i]->price);
  }

  /***************************************************************************/
  /*                       Biggest Ripoff Name                               */
  /***************************************************************************/

  char *name = biggest_ripoff_name(catalog, CATALOG_SIZE);
  printf("\nName of the biggest ripoff item is: %s\n", name);

  /***************************************************************************/
  /*                           Update Material                               */
  /***************************************************************************/

  // Let's create a pointer to a Furniture and the item we need to test 4 and 5
  Furniture *ret;
  ret = update_material(catalog, CATALOG_SIZE, "Docksta table", "Plastic");
  printf("\n%s now has material %s\n", ret->name, ret->material);

  /***************************************************************************/
  /*                         Update Dimensions                               */
  /***************************************************************************/

  Dimensions new_dims = {9.1, 8.1, 7.1, 6.1};

  ret = update_dimensions(catalog, CATALOG_SIZE, "Balkarp sofa", &new_dims);
  printf("\n%s now has dimensions: {%f, %f, %f, %f}\n", ret->name,
         ret->dimensions.height, ret->dimensions.depth, ret->dimensions.width,
         ret->dimensions.weight);

  return 0;
}
#endif
