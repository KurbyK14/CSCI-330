#
# Jacob Kurbis
# z1945650
# CSCI 330 Section 1
# Due 11/07/2022
#


BEGIN {
   
    FS = ":";
}
{
    # This is an employee record
    if ($1 == "E")
    {
        #Store the employee's ID, name, title, and salary
        employeecount++;
        empID[$2] = $2;
        name[$2] = $3;
        title[$2] = $4;
        salary[$2] = $5;

        #Calculating the total salary of all employees
        totalsal += $5 * 1.0;
    }
    # This is a project record
    else if ($1 == "P")
    {
        #Store the project ID, project name, and manager ID
        projectcount++;
        projID[$2] = $2
        projname[$2] = $3;
        managerID[$2] = $4;

    }
    # This is a workingOn record
    else if ($1 == "W")
    {

        #Sorting the employees by project, adding salary totals, and counting the number of employees per project
        if (projID[$4] == 1)
        {
            spiceEmp[$3] = $3;
            totalSpicesal += salary[$3];
            spiceProj++;
        }
        else if (projID[$4] == 2)
        {
            beneEmp[$3] = $3;
            totalBenesal += salary[$3];
            beneProj++;
        }
        else if (projID[$4] == 3)
        {
            jihadEmp[$3] = $3;
            totalJihadsal += salary[$3];
            jihadProj++;
        }
        else if (projID[$4] == 4)
        {
            securityEmp[$3] = $3;
            totalSecuritysal += salary[$3];
            securityProj++;
        }
    } 

}

END {
    #Spice Mining Table Header and Data
    print "|= Spice Mining =============|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";

    for (i in spiceEmp)
    {
        if (i == 140)
        {
            name[i]= "*" name[i];
        }
        printf ("| %-26s | %-20s | %-10s |\n",   name[i], title[i], salary[i]) | "sort -t '|' -nrk4";
    
    }

    #Close sort
    close("sort -t '|' -nrk4");

    #After table statitics
    print "|============================|======================|============|";
    printf ("\tEmployed on Project: %i", spiceProj);
    printf ("\tAverage Salary:  %.2f ", totalSpicesal / spiceProj);
    print "\n\n";
}

END {
    #Bene Gessirit Schemes Table Header and Data
    print "|= Bene Gessirit Schemes ====|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";

    for (i in beneEmp)
    {
        if (i == 192)
        {
            name[i]= "*" name[i];
        }
        printf ("| %-26s | %-20s | %-10s |\n",   name[i], title[i], salary[i]) | "sort -t '|' -nrk4";
    
    }

    #Close sort
    close("sort -t '|' -nrk4");

    #After table statitics
    print "|============================|======================|============|";
    printf ("\tEmployed on Project: %i", beneProj);
    printf ("\tAverage Salary:  %.2f ", totalBenesal / beneProj);
    print "\n\n";
}

END {
    #Muad'Dib's Jihad Table Header and Data
    print "|= Muad'Dib's Jihad =========|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";

    for (i in jihadEmp)
    {
        if (i == 110)
        {
            name[i]= "*" name[i];
        }
        printf ("| %-26s | %-20s | %-10s |\n",   name[i], title[i], salary[i]) | "sort -t '|' -nrk4";
    
    }

    #Close sort
    close("sort -t '|' -nrk4");

    print "|============================|======================|============|";
    printf ("\tEmployed on Project: %i", jihadProj);
    printf ("\tAverage Salary:  %.2f ", totalJihadsal / jihadProj);
    print "\n\n";
}

END {
    #Security Table Header and Data
    print "|= Security =================|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";

    for (i in securityEmp)
    {
        if (i == 130)
        {
            name[i]= "*" name[i];
        }
        printf ("| %-26s | %-20s | %-10s |\n",   name[i], title[i], salary[i]) | "sort -t '|' -nrk4";
    
    }

    #Close sort
    close("sort -t '|' -nrk4");

    #After table statitics
    print "|============================|======================|============|";
    printf ("\tEmployed on Project: %i", securityProj);
    printf ("\tAverage Salary:  %.2f ", totalSecuritysal / securityProj);
    print "\n\n";

    #Printing final statistics
    print "Employees: ", employeecount, " Projects: ", projectcount;
    printf ("Total Salary: %22.2f ", totalsal);
    printf ("\nEmployee Average Salary:  %10.2f ", totalsal / employeecount);
    print "";
}