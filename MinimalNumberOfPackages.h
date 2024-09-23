//
// Created by Adrian Hwang on 2024-09-15.
//

#ifndef HUAWEI_COMPILER_H
#define HUAWEI_COMPILER_H
int MinimalNumberOfPackages(int items, int availableLargePackages, int availableSmallPackages)
{
    int large_hold=5;
    int small_hold=1;

    if(items==0) return 0;

    //firstly use large
    int used_large=items/large_hold;
    int remainder=items%large_hold;
    if(used_large>=availableLargePackages) //no more available large package
    {
        items-=availableLargePackages*large_hold; //all large package are used, remaining items is items
        if(items>availableSmallPackages*small_hold)//no enough small package
        {
            return -1;
        }
        else //enough small package
        {
            return items/small_hold+availableLargePackages;
        }
    }
    else //still have available large package
    {
        return used_large+(remainder>0?1:0);
    }
}
/*package_capability array stores the capability of each package, package_count array stores the available number of each package, package_type_size is the size of package_count array and package_capability array*/
#include <algorithm>
//struct the pair package capability with available count
struct Package
{
    int capability;
    int count;
};
// Custom comparator to sort packages by capability in descending order
bool comparator(const Package& a, const Package& b) {
    return a.capability > b.capability;
}

int MinimalNumberOfPackages2(int items, int package_capability[], int package_available[], int package_type_size)
{
    // Create an array of Package structs
    Package packages[package_type_size];

    // Fill the array with package capability and count
    for (int i = 0; i < package_type_size; i++) {
        packages[i].capability = package_capability[i];
        packages[i].count = package_available[i];
    }

    // Sort packages by capability in descending order
    std::sort(packages, packages + package_type_size, comparator);

    int total_packages_used = 0;

    // Try to pack items using the largest packages first
    for (int i = 0; i < package_type_size; i++) {
        if (items == 0) {
            break; // No more items to pack
        }

        int max_items_from_current_package = packages[i].capability * packages[i].count;

        if (items <= max_items_from_current_package) {
            //We can pack all remaining items using this package type
            //items/packages[i].capability is floor division
            int packages_needed = (items + packages[i].capability - 1) / packages[i].capability; // Ceil division
            total_packages_used += packages_needed;
            items = 0; // All items are packed
        } else {
            // Use all available packages of this type
            total_packages_used += packages[i].count;
            items -= max_items_from_current_package;
        }
    }

    // If there are items left after using all package types, return -1 (failure)
    if (items > 0) {
        return -1;
    }

    return total_packages_used;
}

#endif //HUAWEI_COMPILER_H
