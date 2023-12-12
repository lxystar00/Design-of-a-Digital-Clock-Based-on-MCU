#include <msp430.h> 
#include "oled.h"
#include "bmp.h"
#include <time.h>
#include "key_button.h"
#include<stdio.h>
#include<min_malloc.h>
/**
 * main.c
 */
int num = 0; int hour = 0, hour1, hour2 = 0, hour3 = 0, hour4 = 0, switch2 = 0, switch3 = 0, switch4 = 0; hour_; int minute = 0, minute2 = 0, minute3 = 0, minute4 = 0, minute_; int second = 0, second_;
int year, year1, year2, year3, year4, year_; int month, month1, month2, month3, month4, month_; int day, day2, day3, day4, day_,dayy; int week,number;
unsigned short int key_value, show_key = 0;
int stop,flag,timer_flag;
int day_alarm1=0,day_alarm2=0,day_alarm3=0;
int state = 5; int timer_state = 1;int pm_or_am=0;
unsigned int* Flash_ptr;

char* WEEK[] = { "Sun","Mon","Tue","Wed","Tur","Fri","Sat" };
void SMCLK_XT2_4MHZ(void);
void timer(void);
void data(void);
void set_time(void);
void show_nowdata(void);
void alarm1(void);
void alarm2(void);
void alarm3(void);
void show_alarm(void);
void show_dataandtime(void);
void set_data(void);
void temperature(void);
int get_num2(void);
int get_num4(void);
int ii;
struct shuju   //struct�ṹ�幹��ջ
{
    int data[100];
    int top;
};


/*����ջ*/
struct fuhao
 {
    char symbol[100];
    int top;
};

void InitOperateNum(struct shuju *StackNum)    //����ջ�ǿ�
{
    StackNum->top = -1;
}

void InitOperateSymbol(struct fuhao *StackSymbol)    //����ջ�ǿ�
{
    StackSymbol->top = -1;
}

/*��������ջ*/
void Inshuju(struct shuju *StackNum, int num)
{
    StackNum->top ++;
    StackNum->data[StackNum->top] = num;
}

/*�������ջ*/
void Infuhao(struct fuhao *StackSymbol, char ch)
{
    StackSymbol->top ++;
    StackSymbol->symbol[StackSymbol->top] = ch;
}

/*��ȡ����ջ*/
int Randshuju(struct shuju *StackNum)
{
    return StackNum->data[StackNum->top];
}

/*��ȡ����ջ*/
char Randfuhao(struct fuhao *StackSymbol)
{
    return StackSymbol->symbol[StackSymbol->top];
}

/*������ջȡ������*/
int Putshuju(struct shuju *StackNum)
{
    int x;
    x = StackNum->data[StackNum->top];
    StackNum->top --;
    return x;
}

/*�ӷ���ջȡ������*/
char Putfuhao(struct fuhao *StackSymbol)
{
    char c;
    c = StackSymbol->symbol[StackSymbol->top];
    StackSymbol->top --;
    return c;
}

/*�������ȼ��ж�*/
int judge(char ch) {
    if(ch == '(')
     {
        return 1;
    }
    if(ch == '+' || ch == '-') {
        return 2;
    }
    else if(ch == '*' || ch == '/') {
        return 3;
    }
    else if(ch == ')') {
        return 4;
    }
}

/*��������*/
int Math(int v1, int v2, char c)
{
    int sum;
    switch(c) {
        case '+' :
        {
            sum = v1 + v2;
            break;
        }
        case '-' :
        {
            sum = v1 - v2;
            break;
        }
        case '*' :
        {
            sum = v1 * v2;
            break;
        }
        case '/' :
        {
            sum = v1 / v2;
            break;
        }
    }
    return sum;
}
char getchar1(void)//����getchar����
{
    init_key();
        while(1)
        {
            key_value= key();

            if(key_value==1)
            {return '1';}
            if(key_value==2)
            {return '2';}
            if(key_value==3)
            {return '3';}
            if(key_value==4)
            {return '+';}
            if(key_value==5)
            {return '4';}
            if(key_value==6)
            {return '5';}
            if(key_value==7)
            {return '6';}
            if(key_value==8)
            {return '-';}
            if(key_value==9)
            {return '7';}
            if(key_value==10)
            {return '8';}
            if(key_value==11)
            {return '9';}
            if(key_value==12)
            {return '*';}
            if(key_value==13)
            {return '(';}
            if(key_value==14)
            {return '=';}
            if(key_value==15)
            {return ')';}
            if(key_value==16)
            {return '/';}
            if(key_value==0)
            {return '0';}
            else
            {}
        }
}

void calculate()//���������
{
    OLED_Init();/*init OLED*/
    OLED_Clear(); /*clear OLED screen*/
    struct shuju data;
    struct fuhao symbol;
    InitOperateNum(&data);   //��������
    InitOperateSymbol(&symbol);  //���÷���
    int i,j,q, t, sum, v1, v2;
    char c;
    j=0;i = 6;t =0; sum = 0;q=0;
    char v[100] = {0};
    char *str = (char *)min_malloc(sizeof(char)*200);
    OLED_Init();
    OLED_Clear();
    while((c = getchar1()) != '=')  //�ǿ��ַ�
     {
        if(c!='0')
        {
        str[i] = c;
        if(8*(i-6)<=130)
        {OLED_ShowChar(8*(i-6),0,str[i]);}
        else{OLED_ShowChar(8*j,2,str[i]);j++;}
        i++;
        }
        else
        {
        }
    }
    str[i] = '\0';
    for(i = 6; str[i] != '\0'; i ++)
    {
        if(i == 0 && str[i] == '-')
        {
            v[t++] = str[i];
        }
        else if(str[i] == '(' && str[i+1] == '-')
        {
            i ++;
            v[t++] = str[i++];
            while(str[i] >= '0' && str[i] <= '9')
            {
                v[t] = str[i];
                t ++;
                i ++;
            }
            Inshuju(&data, atoi(v));
            while(t > 0)
            {
                v[t] = 0;
                t --;
            }
            if(str[i] != ')')
            {
                i --;
                Infuhao(&symbol, '(');
            }
        }
        else if(str[i] >= '0' && str[i] <= '9')
        {
            while(str[i] >= '0' && str[i] <= '9')
            {
                v[t] = str[i];
                t ++;
                i ++;
            }
            Inshuju(&data, atoi(v));
            while(t > 0)
            {
                v[t] = 0;
                t --;
            }
            i --;
        }
        else {
            if(symbol.top == -1)
            {        //�������ջû��Ԫ�أ�ֱ�Ӱѷ��ŷ������ջ
                Infuhao(&symbol, str[i]);
            }
            else if(judge(str[i]) == 1)
            { //����˷�����'('��ֱ�ӷ������ջ
                Infuhao(&symbol, str[i]);
            }
            else if(judge(str[i]) == 2)
            { //����˷�����'+'��'-'���ж���ջ�����������ȼ�
                if(judge(Randfuhao(&symbol)) == 1)
                { //���ջ��������'('���������ջ
                    Infuhao(&symbol, str[i]);
                }
                else if(judge(Randfuhao(&symbol)) == 2)
                { //���ջ��������'+'��'-'�����ջ����
                    while(symbol.top >= 0 && data.top >= 1)
                    { //ѭ����ջ
                        v2 = Putshuju(&data);
                        v1 = Putshuju(&data);
                        sum = Math(v1, v2, Putfuhao(&symbol));
                        Inshuju(&data, sum); //��������ѹ������ջ
                    }
                    Infuhao(&symbol, str[i]); //�·��Ž�ջ
                }
                else if(judge(Randfuhao(&symbol)) == 3)
                { //���ջ��������'*'��'/'���������ջ
                    while(symbol.top >= 0 && data.top >= 1)
                    { //ѭ����ջ
                        v2 = Putshuju(&data);
                        v1 = Putshuju(&data);
                        sum = Math(v1, v2, Putfuhao(&symbol));
                        Inshuju(&data, sum); //��������ѹ������ջ
                    }
                    Infuhao(&symbol, str[i]); //�·��Ž�ջ
                }
                /*ջ�����Ų�������')'���ʲ����ж�*/
            }
            else if(judge(str[i]) == 3)
            { //����˷�����'*'��'/'�����ж���ջ�����������ȼ�
                if(judge(Randfuhao(&symbol)) == 1)
                { //���ջ��������'('���������ջ
                    Infuhao(&symbol, str[i]);
                }
                else if(judge(Randfuhao(&symbol)) == 2)
                { //���ջ��������'+'��'-'���������ջ
                    Infuhao(&symbol, str[i]); //�·��Ž�ջ
                }
                else if(judge(Randfuhao(&symbol)) == 3)
                { //���ջ��������'*'��'/'�����ջ����
                    while(symbol.top >= 0 && data.top >= 1)
                    { //ѭ����ջ
                        v2 = Putshuju(&data);
                        v1 = Putshuju(&data);
                        sum = Math(v1, v2, Putfuhao(&symbol));
                        Inshuju(&data, sum); //��������ѹ������ջ
                    }
                    Infuhao(&symbol, str[i]); //�·��Ž�ջ
                }
            }
            else if(judge(str[i]) == 4)
            { // ����˷�����')'�����ջ����ֱ������'('
                do { //ѭ����ջֱ������'('
                    v2 = Putshuju(&data);
                    v1 = Putshuju(&data);
                    sum = Math(v1, v2, Putfuhao(&symbol));
                    Inshuju(&data, sum); //��������ѹ������ջ
                }while(judge(Randfuhao(&symbol)) != 1);
                Putfuhao(&symbol); //���������������ʹ'('��ջ
            }
        }
    }
    free(str); //�ͷ��ڴ�ռ�
    while(symbol.top != -1)
    {
        v2 = Putshuju(&data);
                v1 = Putshuju(&data);
                sum = Math(v1, v2, Putfuhao(&symbol));
                Inshuju(&data, sum);
            }
           OLED_ShowChar(0,6,'=');
           OLED_ShowNum(30,6,data.data[0],6,16);
           __delay_cycles(1000000);
            return 0;
        }
int main(void)//main����
{
     WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    OLED_Init();/*init OLED*/
    OLED_Clear(); /*clear OLED screen*/
    OLED_ShowString(40, 6, "Welcome!");
    __delay_cycles(1000000);
    OLED_Init();/*init OLED*/
    OLED_Clear(); /*clear OLED screen*/

    OLED_ShowString(0, 0, "1.now time+data");
    OLED_ShowString(0, 2, "2.timer");
    OLED_ShowString(0, 4, "3.set time+data");
    OLED_ShowString(0, 6, "4.set alarm");

    init_key();
    while (1)
    {
        key_value = key();

        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 1)
            {
                while (1)
                {
                    OLED_ShowString(0, 0, "1.now time+data");
                    OLED_ShowString(0, 2, "2.timer");
                    OLED_ShowString(0, 4, "3.set time+data");
                    OLED_ShowString(0, 6, "4.set alarm");
                    __delay_cycles(100000); OLED_ShowString(0, 0, "                ");//ѡ�м���˸
                    init_key(); key_value = key(); if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 1)
                        { show_nowdata();timer_flag=0;}
                        else
                            break;
                    }
                }
            }
            else if (key_value == 2)
            {
                while (1)
                {
                    OLED_ShowString(0, 0, "1.now time+data");
                    OLED_ShowString(0, 2, "2.timer");
                    OLED_ShowString(0, 4, "3.set time+data");
                    OLED_ShowString(0, 6, "4.set alarm");
                    __delay_cycles(100000); OLED_ShowString(0, 2, "          ");//ѡ�м���˸
                    init_key(); key_value = key(); if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 2)
                        {
                            OLED_ShowString(0, 6, "                    ");
                            year_ = year; month_ = month; day_ = day;
                            hour_ = hour; minute_ = minute; second_ = second;
                            hour = 0; minute = 0; second = 0; year = 0; month = 0; day = 0;
                            timer_flag=1;
                            timer();

                        }
                        else
                            break;
                    }
                }
            }
            else if (key_value == 3)
            {
                while (1)
                {
                    OLED_ShowString(0, 0, "1.now time+data");
                    OLED_ShowString(0, 2, "2.timer");
                    OLED_ShowString(0, 4, "3.set time+data");
                    OLED_ShowString(0, 6, "4.set alarm");
                    __delay_cycles(100000); OLED_ShowString(0, 4, "               ");//ѡ�м���˸
                    init_key(); key_value = key(); if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 3)
                            {set_time();timer_flag=0;}
                        else
                            break;
                    }

                }
            }
            else if (key_value == 4)
            {
                while (1)
                {
                    OLED_ShowString(0, 0, "1.now time+data");
                    OLED_ShowString(0, 2, "2.timer");
                    OLED_ShowString(0, 4, "3.set time+data");
                    OLED_ShowString(0, 6, "4.set alarm");
                    __delay_cycles(100000); OLED_ShowString(0, 6, "           ");//ѡ�м���˸
                    init_key(); key_value = key();
                    if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 4)
                        { show_alarm();timer_flag=0;}
                        else
                            break;
                    }
                }
            }
            else if (key_value == 5)
            {
                OLED_Init();/*init OLED*/
                OLED_Clear(); /*clear OLED screen*/
                while (1)
                {
                    OLED_ShowString(0, 0, "5.temperature");
                    OLED_ShowString(0, 2, "6.calculator");
                    __delay_cycles(200000); OLED_ShowString(0, 0, "             ");//ѡ�м���˸
                    init_key(); key_value = key(); if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 5)
                            {temperature();timer_flag=0;}
                        else
                            break;
                    }
                }
            }
            else if(key_value==6)
            {
                OLED_Init();
                OLED_Clear();
                while(1)
                {
                    OLED_ShowString(0, 0, "5.temperature");
                    OLED_ShowString(0, 2, "6.calculator");
                    __delay_cycles(200000); OLED_ShowString(0, 2, "             ");//ѡ�м���˸
                    init_key(); key_value = key(); if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 6)
                        {
                            calculate();timer_flag=0;OLED_Init();
                            OLED_Clear();
                        }
                        else
                            break;
                    }
                }
            }
            else {}
            OLED_ShowString(0, 0, "1.now time+data");
            OLED_ShowString(0, 2, "2.timer");
            OLED_ShowString(0, 4, "3.set time+data");
            OLED_ShowString(0, 6, "4.set alarm");
        }
    }
    return 0;
}
#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)   // Temperature Sensor Calibration-30 C
//See device datasheet for TLV table memory mapping
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C

unsigned int temp;
volatile float temperatureDegC;
volatile float temperatureDegF;
int temtemp = 0;

void temperature(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
                                              // ADC12_A ref control registers
    ADC12CTL0 = ADC12SHT0_8 + ADC12REFON + ADC12ON;
    // Internal ref = 1.5V
    ADC12CTL1 = ADC12SHP;                     // enable sample timer
    ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC i/p ch A10 = temp sense i/p
    ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO
    __delay_cycles(100);                      // Allow ~100us (at default UCS settings)
                                              // for REF to settle
    ADC12CTL0 |= ADC12ENC;

    OLED_Init();
    OLED_Clear();
    init_key();
    while (1)
    {
        ADC12CTL0 &= ~ADC12SC;
        ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start

        __bis_SR_register(LPM4_bits + GIE);     // LPM0 with interrupts enabled
        __no_operation();

        // Temperature in Celsius. See the Device Descriptor Table section in the
        // System Resets, Interrupts, and Operating Modes, System Control Module
        // chapter in the device user's guide for background information on the
        // used formula.
        temperatureDegC = (float)(((long)temp - CALADC12_15V_30C) * (85 - 30)) /
            (CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f; //���϶���ʾ

        temtemp = temperatureDegC * 100;
        OLED_ShowString(1, 0, "Temp=");
        OLED_ShowString(57, 0, ".");
        OLED_ShowNum(41, 0, temtemp / 100, 2, 16);
        OLED_ShowNum(65, 0, temtemp % 100, 2, 16);    //�¶���ʾ
        key_value = key();
        if (key_value != 0)
        {
            key_value = key();   /*scan Array_button, get the key value*/
            if (key_value == 10)
            {
                return;
            }
        }

        // Temperature in Fahrenheit Tf = (9/5)*Tc + 32
        temperatureDegF = temperatureDegC * 9.0f / 5.0f + 32.0f;//���϶Ȼ���
        _delay_cycles(100000);
        __no_operation();                       // SET BREAKPOINT HERE
    }
}
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void)
{
    switch (__even_in_range(ADC12IV, 34))
    {
    case  0: break;                           // Vector  0:  No interrupt
    case  2: break;                           // Vector  2:  ADC overflow
    case  4: break;                           // Vector  4:  ADC timing overflow
    case  6:                                  // Vector  6:  ADC12IFG0
        temp = ADC12MEM0;                       // Move results, IFG is cleared
        __bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU
    case  8: break;                           // Vector  8:  ADC12IFG1
    case 10: break;                           // Vector 10:  ADC12IFG2
    case 12: break;                           // Vector 12:  ADC12IFG3
    case 14: break;                           // Vector 14:  ADC12IFG4
    case 16: break;                           // Vector 16:  ADC12IFG5
    case 18: break;                           // Vector 18:  ADC12IFG6
    case 20: break;                           // Vector 20:  ADC12IFG7
    case 22: break;                           // Vector 22:  ADC12IFG8
    case 24: break;                           // Vector 24:  ADC12IFG9
    case 26: break;                           // Vector 26:  ADC12IFG10
    case 28: break;                           // Vector 28:  ADC12IFG11
    case 30: break;                           // Vector 30:  ADC12IFG12
    case 32: break;                           // Vector 32:  ADC12IFG13
    case 34: break;                           // Vector 34:  ADC12IFG14
    default: break;
    }
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    P8OUT ^= BIT0;//P8.1�Ƶķ�ת
    num++;
    if (num > 119)
    {
        num = 0;
    }
    if (num % 2 == 0)
    {
        FCTL1 = FWKEY + ERASE;//����
        FCTL3 = FWKEY;
        *Flash_ptr = 0;
        FCTL1 = FWKEY + WRT;//д��ģʽ
        *Flash_ptr = year;
        *(Flash_ptr + 1) = month;
        *(Flash_ptr + 2) = day;
        *(Flash_ptr + 3) = hour;//д��
        *(Flash_ptr + 4) = minute;
        *(Flash_ptr + 5) = second;
        FCTL1 = FWKEY;
        FCTL3 = FWKEY + LOCK;//�ر�д��

        if (stop == 1)
        {
            while (1)
            {
                key_value = key();
                if (key_value != 0)
                {
                    key_value = key();   /*scan Array_button, get the key value*/
                    if (key_value == 13)
                        break;
                }
            }
        }
        else
        {
            if (second < 59)
                {second++;}
            else
            {
                second = 0;
                if (minute < 59)
                    {minute++;}
                else
                {
                    second = 0; minute = 0;hour1++;
                    if(hour==13&&timer_state%2==1)
                       hour=1;
                    else
                    {
                    }
                    if(((timer_state%2==0)&&(hour<23))||((timer_state%2==1)&&hour<13))//��flag�ж�Сʱ�Ľ�λ
                        hour++;
                    else
                    {
                        if(timer_state%2==0)
                        { hour = 0;minute = 0; second = 0; day++;}
                        else if((timer_state%2==1)&&(pm_or_am%2==1)&&(hour==11))
                        {hour=12;minute = 0; second = 0;/*day++;*/}
                        else
                        {
                        }
                        if (month == 12 && day == 32)
                        {year++; month = 1; day = 1;}
                        if ((month == 1||month == 3||month == 5||month == 7||month == 8||month == 10) && day == 32)
                        { month++; day = 1;}
                        if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
                        {month++; day = 1;}
                        if (month == 2 && ((year % 100 == 0 && year % 400 != 0) || (year % 100 != 0 && year % 4 != 0)) && day == 29)
                        {month++; day = 1;}
                        if (month == 2 && (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && day == 30)
                        {month++; day = 1;}
                        else {}
                    }
                }
            }
        }
    }
}
void show_alarm(void)//չʾʱ��
{
    OLED_Init();/*init OLED*/
    OLED_Clear(); /*clear OLED screen*/
    OLED_ShowChar(10, 0, '1'); OLED_ShowNum(20, 0, hour2, 2, 16); OLED_ShowChar(36, 0, ':'); OLED_ShowNum(40, 0, minute2, 2, 16); if (switch2 % 2 == 0)OLED_ShowString(60, 0, "off"); else OLED_ShowString(60, 0, "on ");
    OLED_ShowChar(10, 2, '2'); OLED_ShowNum(20, 2, hour3, 2, 16); OLED_ShowChar(36, 2, ':'); OLED_ShowNum(40, 2, minute3, 2, 16); if (switch3 % 2 == 0)OLED_ShowString(60, 2, "off"); else OLED_ShowString(60, 2, "on ");
    OLED_ShowChar(10, 4, '3'); OLED_ShowNum(20, 4, hour4, 2, 16); OLED_ShowChar(36, 4, ':'); OLED_ShowNum(40, 4, minute4, 2, 16); if (switch4 % 2 == 0)OLED_ShowString(60, 4, "off"); else OLED_ShowString(60, 4, "on ");
    while (1)
    {
        key_value = key();
        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 10)
            {return;}
            if (key_value == 1)
            {
                while (1)
                {
                    OLED_ShowChar(10, 0, '1'); OLED_ShowNum(20, 0, hour2, 2, 16); OLED_ShowChar(36, 0, ':'); OLED_ShowNum(40, 0, minute2, 2, 16); if (switch2 % 2 == 0)OLED_ShowString(60, 0, "off"); else OLED_ShowString(60, 0, "on ");
                    OLED_ShowChar(10, 2, '2'); OLED_ShowNum(20, 2, hour3, 2, 16); OLED_ShowChar(36, 2, ':'); OLED_ShowNum(40, 2, minute3, 2, 16); if (switch3 % 2 == 0)OLED_ShowString(60, 2, "off"); else OLED_ShowString(60, 2, "on ");
                    OLED_ShowChar(10, 4, '3'); OLED_ShowNum(20, 4, hour4, 2, 16); OLED_ShowChar(36, 4, ':'); OLED_ShowNum(40, 4, minute4, 2, 16); if (switch4 % 2 == 0)OLED_ShowString(60, 4, "off"); else OLED_ShowString(60, 4, "on ");
                    __delay_cycles(100000); OLED_ShowString(0, 0, "                ");//ѡ�м���˸
                    init_key(); key_value = key(); if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 1)
                            alarm1();
                        else if (key_value == 16)
                        { switch2++;}//��������1�Ĺرջ��
                        else
                            break;
                    }
                }
            }
            else if (key_value == 2)
            {
                while (1)
                {
                    OLED_ShowChar(10, 0, '1'); OLED_ShowNum(20, 0, hour2, 2, 16); OLED_ShowChar(36, 0, ':'); OLED_ShowNum(40, 0, minute2, 2, 16); if (switch2 % 2 == 0)OLED_ShowString(60, 0, "off"); else OLED_ShowString(60, 0, "on ");
                    OLED_ShowChar(10, 2, '2'); OLED_ShowNum(20, 2, hour3, 2, 16); OLED_ShowChar(36, 2, ':'); OLED_ShowNum(40, 2, minute3, 2, 16); if (switch3 % 2 == 0)OLED_ShowString(60, 2, "off"); else OLED_ShowString(60, 2, "on ");
                    OLED_ShowChar(10, 4, '3'); OLED_ShowNum(20, 4, hour4, 2, 16); OLED_ShowChar(36, 4, ':'); OLED_ShowNum(40, 4, minute4, 2, 16); if (switch4 % 2 == 0)OLED_ShowString(60, 4, "off"); else OLED_ShowString(60, 4, "on ");
                    __delay_cycles(100000); OLED_ShowString(0, 2, "                ");//ѡ�м���˸
                    init_key(); key_value = key(); if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 2)
                            alarm2();
                        else if (key_value == 16)
                        {switch3++;}//��������1�Ĺرջ��
                        else
                            break;
                    }
                }
            }
            else if (key_value == 3)
            {
                while (1)
                {
                    OLED_ShowChar(10, 0, '1'); OLED_ShowNum(20, 0, hour2, 2, 16); OLED_ShowChar(36, 0, ':'); OLED_ShowNum(40, 0, minute2, 2, 16); if (switch2 % 2 == 0)OLED_ShowString(60, 0, "off"); else OLED_ShowString(60, 0, "on ");
                    OLED_ShowChar(10, 2, '2'); OLED_ShowNum(20, 2, hour3, 2, 16); OLED_ShowChar(36, 2, ':'); OLED_ShowNum(40, 2, minute3, 2, 16); if (switch3 % 2 == 0)OLED_ShowString(60, 2, "off"); else OLED_ShowString(60, 2, "on ");
                    OLED_ShowChar(10, 4, '3'); OLED_ShowNum(20, 4, hour4, 2, 16); OLED_ShowChar(36, 4, ':'); OLED_ShowNum(40, 4, minute4, 2, 16); if (switch4 % 2 == 0)OLED_ShowString(60, 4, "off"); else OLED_ShowString(60, 4, "on ");
                    __delay_cycles(100000); OLED_ShowString(0, 4, "                ");//ѡ�м���˸
                    init_key(); key_value = key(); if (key_value != 0)
                    {
                        key_value = key();
                        if (key_value == 3)
                            alarm3();
                        else if (key_value == 16)
                        {switch4++;}//��������1�Ĺرջ��
                        else
                            break;
                    }
                }
            }
            else
            {
                OLED_ShowChar(10, 0, '1'); OLED_ShowNum(20, 0, hour2, 2, 16); OLED_ShowChar(36, 0, ':'); OLED_ShowNum(40, 0, minute2, 2, 16); if (switch2 % 2 == 0)OLED_ShowString(60, 0, "off"); else OLED_ShowString(60, 0, "on ");
                OLED_ShowChar(10, 2, '2'); OLED_ShowNum(20, 2, hour3, 2, 16); OLED_ShowChar(36, 2, ':'); OLED_ShowNum(40, 2, minute3, 2, 16); if (switch3 % 2 == 0)OLED_ShowString(60, 2, "off"); else OLED_ShowString(60, 2, "on ");
                OLED_ShowChar(10, 4, '3'); OLED_ShowNum(20, 4, hour4, 2, 16); OLED_ShowChar(36, 4, ':'); OLED_ShowNum(40, 4, minute4, 2, 16); if (switch4 % 2 == 0)OLED_ShowString(60, 4, "off"); else OLED_ShowString(60, 4, "on ");
            }
        }
    }
}
void alarm1(void)//��������1
{
    int state2 = 1;
    init_key();
    while (1)
    {
        key_value = key();

        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 1)
            {
                state2++;
                switch (state2 % 2)
                {
                case 0: { OLED_Init();
                    OLED_Clear(); OLED_ShowString(0, 6, "hour="); hour2 = get_num2(); OLED_ShowNum(60, 6, hour2, 2, 16); __delay_cycles(1000000); }
                case 1: { OLED_Init();
                    OLED_Clear(); OLED_ShowString(0, 6, "minute="); minute2 = get_num2(); OLED_ShowNum(60, 6, minute2, 2, 16); __delay_cycles(1000000); }
                default:break;
                }
                OLED_Init();
                OLED_Clear();
                return;
            }
        }
    }
}
void alarm2(void)//��������2
{
    int state2 = 1;
    init_key();
    while (1)
    {
        key_value = key();

        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 2)
            {
                state2++;
                switch (state2 % 2)
                {
                case 0: { OLED_Init();
                    OLED_Clear(); OLED_ShowString(0, 6, "hour="); hour3 = get_num2(); OLED_ShowNum(60, 6, hour3, 2, 16); __delay_cycles(1000000); }
                case 1: { OLED_Init();
                    OLED_Clear(); OLED_ShowString(0, 6, "minute="); minute3 = get_num2(); OLED_ShowNum(60, 6, minute3, 2, 16); __delay_cycles(1000000); }
                default:break;
                }
                OLED_Init();
                OLED_Clear();
                return;
            }
        }
    }
}
void alarm3(void)//��������3
{
    int state2 = 1;
    init_key();
    while (1)
    {
        key_value = key();

        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 3)
            {
                state2++;
                switch (state2 % 2)
                {
                case 0: { OLED_Init();
                    OLED_Clear(); OLED_ShowString(0, 6, "hour="); hour4 = get_num2(); OLED_ShowNum(60, 6, hour4, 2, 16); __delay_cycles(1000000); }
                case 1: { OLED_Init();
                    OLED_Clear(); OLED_ShowString(0, 6, "minute="); minute4 = get_num2(); OLED_ShowNum(60, 6, minute4, 4, 16); __delay_cycles(1000000); }
                default:break;
                }
                OLED_Init();
                OLED_Clear();
                return;
            }
        }
    }
}
void SMCLK_XT2_4MHZ(void)
{
    P7SEL |= BIT2 + BIT3;
    UCSCTL6 &= ~XT2OFF;
    UCSCTL6 &= ~XT2OFF + XT2DRIVE_1;
    UCSCTL3 |= SELREF_2;

    // cause

    UCSCTL4 |= SELA_2;
    // ACLK=REFO,SMCLK=DCO,MCLK=DCO
    do
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
        //flags
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1 & OFIFG);
    UCSCTL6 &= ~XT2DRIVE0;
    // according to
    UCSCTL4 |= SELS_5 + SELM_5;
}
void show_nowdata(void)//��ȡ���Ե�ǰ��������ʱ��
{
    char* wday[] = { "Sun","Mon","Tue","Wed","Tur","Fri","Sat" };
    time_t timep;
    struct tm* p;
    time(&timep);
    p = localtime(&timep);
    OLED_Init();
    OLED_Clear();

    year = 1900 + p->tm_year;
    month = 1 + p->tm_mon;
    day = p->tm_mday;
    hour = 14 + p->tm_hour;
    minute = p->tm_min;
    second = p->tm_sec;
    OLED_ShowNum(0, 6, 1900 + p->tm_year, 4, 16);
    OLED_ShowChar(32, 6, '/');
    OLED_ShowNum(38, 6, 1 + p->tm_mon, 2, 16);
    OLED_ShowChar(53, 6, '/');
    OLED_ShowNum(60, 6, p->tm_mday, 2, 16);
    OLED_ShowString(80, 6, wday[p->tm_wday]);
    OLED_ShowNum(0, 8, 14 + p->tm_hour, 2, 16);
    OLED_ShowChar(16, 8, ':');
    OLED_ShowNum(23, 8, p->tm_min, 2, 16);
    OLED_ShowChar(39, 8, ':');
    OLED_ShowNum(46, 8, p->tm_sec, 2, 16);
    while (1)
    {
        key_value = key();

        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 10)//����10����
            {return;}
        }

        time_t timep;
        struct tm* p;
        time(&timep);
        p = localtime(&timep);
        OLED_ShowNum(0, 8, 14+p->tm_hour, 2, 16);
        OLED_ShowChar(16, 8, ':');
        OLED_ShowNum(23, 8, p->tm_min, 2, 16);
        OLED_ShowChar(39, 8, ':');
        OLED_ShowNum(46, 8, p->tm_sec, 2, 16);
    }
}
void timer(void)//����ʱ��
{
    int data_or_not = 0;
    OLED_Init();
    OLED_Clear();
    SMCLK_XT2_4MHZ();

    Flash_ptr = (unsigned int*)0x001800;
    UCSCTL5 |= DIVS__32;
    TA0CTL |= ID_2 + TASSEL_2 + MC_1 + TACLR;
    TA0EX0 |= TAIDEX_4;
    TA0CCTL0 = OUTMOD_2 + CCIE;
    TA0CCR0 = 3125;

    P8DIR |= BIT0;
    P8OUT &= ~BIT0;
    P5DIR |= BIT0;
    P5DIR |= BIT1;
    P3DIR |= BIT3;//��������ܽ�

    P5OUT |= BIT0;//����Ĭ��״̬Ϊ����
    P5OUT |= BIT1;
    P3OUT |= BIT3;

    /*year=*Flash_ptr;
    month=*(Flash_ptr+1);
    day=*(Flash_ptr+2);
    hour=*(Flash_ptr+3);
    minute=*(Flash_ptr+4);
    second=*(Flash_ptr+5);*/
    *Flash_ptr = year;
    *(Flash_ptr + 1) = month;
    *(Flash_ptr + 2) = day;
    *(Flash_ptr + 3) = hour;
    *(Flash_ptr + 4) = minute;
    *(Flash_ptr + 5) = second;

    if(timer_flag==1)
    {
        OLED_ShowString(80, 8, "  ");
    }
    else
    {
    if(timer_state%2==1)//�ж���12ʱ��
    {
        if(pm_or_am%2==0)//�ж���am or pm
            OLED_ShowString(80, 8, "AM");
        else
            OLED_ShowString(80, 8, "PM");
    }
    else
    {
        OLED_ShowString(80, 8, "  ");
    }
    }
    OLED_ShowNum(0, 8, hour, 2, 16);
    OLED_ShowChar(16, 8, ':');
    OLED_ShowNum(23, 8, minute, 2, 16);
    OLED_ShowChar(39, 8, ':');
    OLED_ShowNum(46, 8, second, 2, 16);
    if ((year == 0) && (month == 0) && (day == 0))
    {
        data_or_not = -1;
    }
    else
    {
        OLED_ShowNum(0, 6, year, 4, 16);
        OLED_ShowChar(33, 6, '/');
        OLED_ShowNum(40, 6, month, 2, 16);
        OLED_ShowChar(59, 6, '/');
        OLED_ShowNum(69, 6, day, 2, 16);
    }
    int c;
    int y;

    y = year - year % 100;//��ݺ���λ
    c = year / 100;//���ǰ��λ
    month1 = month; year1 = year;
    if (month == 1 || month == 2)
    {
        month += 12; year--;
    }
    week = (year + year / 4 + c / 4 - 2 * c + 26 * (month + 1) / 10 + day - 2) % 7;//��������
    month = month1; year = year1; hour1 = hour;

    __bis_SR_register(GIE);//�ж�����
    while (1)
    {
        while(1)
        {
                                             if((timer_state%2==1)&&(pm_or_am%2==1)&&(hour==12)&&(minute==0)&&(second==0))
                                             {hour=12;pm_or_am=0;if(pm_or_am%2==0) OLED_ShowString(80, 8, "AM"); else OLED_ShowString(80, 8, "PM");day=dayy+1;break;}
                                             else if((timer_state%2==1)&&(pm_or_am%2==0)&&(hour==12)&&(minute==0)&&(second==0))
                                             {hour=12;pm_or_am=1;if(pm_or_am%2==0) OLED_ShowString(80, 8, "AM"); else OLED_ShowString(80, 8, "PM");day=dayy;  break;}
                                             else if((timer_state%2==1)&&(pm_or_am%2==1)&&(hour==13)&&(minute==0)&&(second==0))
                                             {hour=1;if(pm_or_am%2==0) OLED_ShowString(80, 8, "AM"); else OLED_ShowString(80, 8, "PM");break;}
                                             else if((timer_state%2==1)&&(pm_or_am%2==0)&&(hour==13)&&minute==0&&(second==0))
                                             {hour=1;if(pm_or_am%2==0) OLED_ShowString(80, 8, "AM"); else OLED_ShowString(80, 8, "PM");break;}
                                             else{break;}
        }
        key_value = key();
        if (key_value != 0)
        {

            key_value = key();   /*scan Array_button, get the key value*/
            if (key_value == 10)
            {
                year = year_; month_ = month; day_ = day;
                hour = hour_; minute = minute_; second = second_;
                return;
            }
            if (key_value == 12)
            {stop = 1;}//��ͣ

            if (key_value == 13)
            {stop = 0;}//��ʼ

            if (key_value == 14)
            {hour = 0; minute = 0; second = 0;}//����

            if (key_value == 11)//����ʱ��
            {
                timer_state++;
                switch (timer_state % 2)
                {
                case 0: {if(pm_or_am%2==0) {if(hour==12) hour=0;else hour=hour1;}
                if(pm_or_am%2==1){if(hour==12) hour=12;else hour=hour+12;}
                        OLED_ShowString(80, 8, "  "); break;}
                case 1:
                {
                    if(hour==0)
                    {OLED_ShowString(80, 8, "AM");pm_or_am=0;hour=12; break;}
                    else if(0<hour&&hour<12)
                    {OLED_ShowString(80, 8, "AM");pm_or_am=0; break;}
                    else if(hour==12)
                    {OLED_ShowString(80, 8, "PM");pm_or_am=1; break;}
                    else if(hour>12)
                    {OLED_ShowString(80, 8, "PM");hour=hour-12;pm_or_am=0; break;}

                }
                default:break;
                }
            }
        }
        month1 = month;
        if (month == 1 || month == 2)
        {month += 12; year--;}

        week = (year + year / 4 + c / 4 - 2 * c + 26 * (month + 1) / 10 + day - 2) % 7;
        month = month1; year = year1;
        if (((switch2 % 2 == 1) && (hour == hour2) && (minute == minute2)&&(day!=day_alarm1)) || ((switch3 % 2 == 1) && (hour == hour3) && (minute == minute3)&&(day!=day_alarm2)) || ((switch4 % 2 == 1) && (hour == hour4) && (minute == minute4)&&(day!=day_alarm3)))//���ӹ���
        {
            P5OUT ^= BIT0; __delay_cycles(100000); P5OUT ^= BIT0;//����ˮ�ƴ��������
            P5OUT ^= BIT1; __delay_cycles(100000); P5OUT ^= BIT1;
            P3OUT ^= BIT3; __delay_cycles(100000); P3OUT ^= BIT3;
           while(1)
           {
            key_value = key();
            if(key_value!=0)
            {
                key_value = key();
            if(key_value==15)
            {
                if((switch2 % 2 == 1) && (hour == hour2) && (minute == minute2))
                    {day_alarm1=day;break;}
                else if((switch3 % 2 == 1) && (hour == hour3) && (minute == minute3))
                    {day_alarm2=day;break;}
                else if((switch4 % 2 == 1) && (hour == hour4) && (minute == minute4))
                    {day_alarm3=day;break;}
            }
            else break;
           }
            else
                break;
           }
        }
        else
        {}
        if (data_or_not == -1)
        {}
        else
        {
            OLED_ShowString(89, 6, WEEK[week]);
            OLED_ShowNum(0, 6, *Flash_ptr, 4, 16);
            OLED_ShowChar(33, 6, '/');
            OLED_ShowNum(40, 6, *(Flash_ptr + 1), 2, 16);
            OLED_ShowChar(59, 6, '/');
            OLED_ShowNum(69, 6, *(Flash_ptr + 2), 2, 16);
        }
        if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))&&timer_flag==0)//�ж�����
            OLED_ShowString(0, 4, "leap year");

        OLED_ShowNum(0, 8, *(Flash_ptr + 3), 2, 16);
        OLED_ShowChar(16, 8, ':');
        OLED_ShowNum(23, 8, *(Flash_ptr + 4), 2, 16);
        OLED_ShowChar(39, 8, ':');
        OLED_ShowNum(46, 8, *(Flash_ptr + 5), 2, 16);
    }
}
void set_time(void)
{
    state = -1;

    OLED_Init();
    OLED_Clear();
    OLED_ShowNum(0, 8, hour, 2, 16);
    OLED_ShowChar(16, 8, ':');
    OLED_ShowNum(23, 8, minute, 2, 16);
    OLED_ShowChar(39, 8, ':');
    OLED_ShowNum(46, 8, second, 2, 16);
    OLED_ShowNum(0, 6, year, 4, 16);
    OLED_ShowChar(33, 6, '/');
    OLED_ShowNum(40, 6, month, 2, 16);
    OLED_ShowChar(59, 6, '/');
    OLED_ShowNum(69, 6, day, 2, 16);
    init_key();
    if(timer_state%2==0)//��ʾ��ǰ���õ�ʱ��
    {
        OLED_ShowNum(59, 4, 24, 2, 16);
        OLED_ShowString(80, 4,"  ");
    }
    else
        {
        OLED_ShowNum(59, 4, 12, 2, 16);
    if(pm_or_am%2==0)//��ʾ��ǰ12ʱ�Ƶ�״̬
        OLED_ShowString(80, 4,"AM");
    else
        OLED_ShowString(80, 4,"PM");
        }
    while (1)
    {
        key_value = key();

       /* if(pm_or_am%2==0)
            OLED_ShowString(80, 4,"AM");
        else
            OLED_ShowString(80, 4,"PM");*/
        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 11)//�л�ʱ��
            {
                timer_state++;
                if(timer_state%2==0)
                        {OLED_ShowNum(59, 4, 24, 2, 16);OLED_ShowString(80, 4,"  ");}
                else
                        OLED_ShowNum(59, 4, 12, 2, 16);
            }
            if((key_value==15)&&(timer_state%2==1))//�л�am or pm
            {
                pm_or_am++;
                if(pm_or_am%2==0)
                    OLED_ShowString(80, 4,"AM");
                else
                    OLED_ShowString(80, 4,"PM");
            }
            if (key_value == 12)//��ʼ����ʱ��������
            {
                state++;
                OLED_ShowNum(69, 4, state % 6, 2, 16);

                switch (state % 6)
                {
                case 0: { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "hour="); hour = get_num2(); OLED_ShowNum(60, 6, hour, 2, 16); __delay_cycles(1000000); while ((timer_state%2==0)&&(hour > 24)||(timer_state%2==1)&&(hour>12||hour==0)) { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "hour="); hour = get_num2(); OLED_ShowNum(60, 6, hour, 2, 16); __delay_cycles(1000000); }}
                case 1: {OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "minute="); minute = get_num2(); OLED_ShowNum(60, 6, minute, 2, 16); __delay_cycles(1000000); while (minute > 60) { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "minute="); minute = get_num2(); OLED_ShowNum(60, 6, minute, 2, 16); __delay_cycles(1000000); }}
                case 2: { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "second="); second = get_num2();OLED_ShowNum(60, 6, second, 2, 16); __delay_cycles(1000000); while (second > 60) { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "second="); second = get_num2(); OLED_ShowNum(60, 6, second, 2, 16); __delay_cycles(1000000); }}
                case 3: { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "year="); year = get_num4(); OLED_ShowNum(60, 6, year, 4, 16); __delay_cycles(1000000); }
                case 4: { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "month="); month = get_num2(); OLED_ShowNum(60, 6, month, 2, 16); __delay_cycles(1000000); while (month > 13 || month == 0) { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "month="); month = get_num2(); OLED_ShowNum(60, 6, month, 2, 16); __delay_cycles(1000000); }}
                case 5: { OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "day="); day = get_num2();dayy=day; OLED_ShowNum(60, 6, day, 2, 16); __delay_cycles(1000000);
                    while (((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10||month==12) && day > 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (month == 2 && ((year % 100 == 0 && year % 400 != 0) || (year % 100 != 0 && year % 4 != 0)) && day > 28) || (month == 2 && (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && day > 29) || day == 0)
                    {
                        OLED_Init(); OLED_Clear(); OLED_ShowString(0, 6, "day="); day = get_num2(); OLED_ShowNum(60, 6, day, 2, 16); __delay_cycles(1000000);
                    }}
                default:break;
                }
                timer();
            }
            if (key_value == 10)
                return;
        }
    }
}
int get_num4(void)//��ȡ4λ��
{
    int count = 0;
    int number;
    int Array[4];
    init_key();
    while (1)
    {
        key_value = key();
        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 16)
            { key_value = 0;}

            Array[count] = key_value;
            init_key();
            key_value = key();
            __delay_cycles(10000);
            count++;
            if (count == 4)
            {count = 0; break;}
        }
    }
    number = Array[0] * 1000 + Array[1] * 100 + Array[2] * 10 + Array[3];
    return number;
}
int get_num2(void)//��ȡ2λ��
{
    int count = 0;
    int number;
    int Array[2];
    init_key();
    while (1)
    {
        key_value = key();

        if (key_value != 0)
        {
            key_value = key();
            if (key_value == 16)
            {key_value = 0;}

            Array[count] = key_value;
            init_key();
            key_value = key();
            __delay_cycles(10000);
            count++;
            if (count == 2)
            {count = 0; break;}
        }
    }
    number = 10 * Array[0] + Array[1];
    return number;
}
