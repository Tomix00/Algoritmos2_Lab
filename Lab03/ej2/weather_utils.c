#include "weather_utils.h"

int menor_temperatura_minima(WeatherTable array){
    int min=INT_MAX;
    for(unsigned int i=0;i<YEARS;i++){
        for(unsigned int j=0;j<MONTHS;j++){
            for(unsigned int k=0;k<DAYS;k++){
                if(array[i][j][k]._min_temp<min){
                    min = array[i][j][k]._min_temp;
                }
            }
        }
    }
    return min;
}


void mayor_temperatura_maxima(WeatherTable array,int maximos[YEARS]){
    int max=INT_MIN;
    for(unsigned int i=0;i<YEARS;i++){
        for(unsigned int j=0;j<MONTHS;j++){
            for(unsigned int k=0;k<DAYS;k++){
                if(array[i][j][k]._max_temp>max){
                    max = array[i][j][k]._max_temp;
                }
            }
        }

        maximos[i]=max;
        max=INT_MIN;
    }
}


void precipitaciones(WeatherTable array, int meses_p[YEARS]){
    int precs[MONTHS];
    int count=0;
    int max = INT_MIN;

    for(unsigned int year=0;year<YEARS;year++){
        for (unsigned int month=0;month<MONTHS;month++){
            for (unsigned int day=0;day<DAYS;day++){
                if(array[year][month][day]._rainfall != 0){
                    count++;
                }
            }
            precs[month]=count;
            count = 0;
        }
        
        /*comparo la lista de precipitaciones*/
        for(unsigned int i=0;i<MONTHS;i++){
            if(precs[i]>max){
                max = precs[i];
            }
        }

        meses_p[year]=max;
    }
}

