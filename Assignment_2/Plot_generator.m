clc
clear all
filename = 'F:\Academics\SEM 7\D_ID6105\Assignment_2\SimStockVal.txt';
delimiter = ',';
startRow = 2;
formatSpec = '%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'EmptyValue' ,NaN,'HeaderLines' ,startRow-1, 'ReturnOnError', false);
fclose(fileID);
Days = dataArray{:, 1};
StockPrice = dataArray{:, 2};
plot(Days,StockPrice);
title('Stock Price Prediction');
xlabel('Days')
ylabel('Stock Value')
filename = 'F:\Academics\SEM 7\D_ID6105\Assignment_2\RandVal.txt';
delimiter = ',';
startRow = 2;
formatSpec = '%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'EmptyValue' ,NaN,'HeaderLines' ,startRow-1, 'ReturnOnError', false);
fclose(fileID);
Days = dataArray{:, 1};
RandVal = dataArray{:, 2};
figure,
hist(RandVal,5,'Normalization','probability');
%histfit(RandVal,5);
xlabel('Random index generated')
ylabel('Count')
title('Distribution of Random Variable')