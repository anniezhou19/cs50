# include <stdio.h>
# include <cs50.h>
# include <math.h>

// AMEX: 15-Digit #'s, Star with: 34 or 37
// MASTERCARD: 16-Digit #'s, Start with: 51, 52, 53, 54, or 55
// VISA: 13-16-Digit #'s, Start with: 4

int main(void)
{
    long credit_number;
    long copy_credit;
    int total_sum = 0, pos = 0, total_length = 0;
    do
    {
        credit_number = get_long("Number: ");
        copy_credit = credit_number;
    }
    while (credit_number < 0);

    while (credit_number != 0)
    {
        if (pos % 2 != 0)
        {
            int temp = 2 * (credit_number % 10);
            if (temp > 9)
            {
                total_sum += (temp / 10 + temp % 10);
            }
            else
            {
                total_sum += temp;
            }
        }

        else
        {
            total_sum += credit_number % 10;
        }
        credit_number = credit_number / 10;
        pos++;
        total_length++;
    }

    if (total_sum % 10 == 0)
    {
        long amx_start = copy_credit / 10000000000000;
        if ((amx_start == 34 || amx_start == 37) && (total_length == 15))
        {
            printf("AMEX\n");
            return 0;
        }
        long master_start = copy_credit / 100000000000000;
        if ((master_start >= 51 && master_start <= 55) && (total_length == 16))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        long visa_start = copy_credit / 1000000000000;
        if ((visa_start == 4 || visa_start / 1000 == 4) && (total_length == 13 || total_length == 16))
        {
            printf("VISA\n");
            return 0;
        }
        printf("INVALID\n");

    }
    else
    {
        printf("INVALID\n");
    }

}
