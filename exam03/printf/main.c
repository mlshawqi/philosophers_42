#include <unistd.h>
#include <stdarg.h>


int     ft_format(char c, int *len, va_list args)
{
        if(c == 'd')
                ft_putnbr(va_arg(args, int), len);
        else if(c == 's')
                ft_putstr(va_arg(args, char *), len);
        else if(c == 'x')
                ft_puthex(va_arg(args, unsigned int), len);
}

int ft_printf(const char *str, ... )
{
        va_list arg;
        int     count;

        va_start(arg, str);
        count = 0;
        while(*str)
        {
                if(*str == '%')
                {
                        *str++;
                        ft_format(*str, &count, arg);
                }
                else
                {
                        write(1, &str, 1);
                        *str++;
                        count++;
                }
        }
        return (count);
}