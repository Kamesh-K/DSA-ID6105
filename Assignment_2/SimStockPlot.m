function [y] = SimStockPlot(n)
    clc;
    close all;
    i=0;
    n=n-1;
    s='F:\Academics\SEM 7\D_ID6105\Assignment_2\SimStockVal';
    txt='.txt';
    str='legend';
    legend_mat=[];
    for i=0:n
    filename=strcat(s,num2str(i),txt);    
    delimiter = ',';
    startRow = 2;
    formatSpec = '%f%f%[^\n\r]';
    fileID = fopen(filename,'r');
    dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'EmptyValue' ,NaN,'HeaderLines' ,startRow-1, 'ReturnOnError', false);
    fclose(fileID);
    Days = dataArray{:, 1};
    StockPrice = dataArray{:, 2};
    hold on 
    plot(Days,StockPrice);
    str=strcat('Stock ',num2str(i));
    legend_mat=[legend_mat; str];
    end
    legend(legend_mat,'Location','SouthWest');
    xlabel('Days');
    ylabel('Stock Price');
    title('Simulation of Stocks');
    figure,
    i=0;
    s='F:\Academics\SEM 7\D_ID6105\Assignment_2\MovingAverage';
    legend_mat=[];
    for i=0:n
    filename=strcat(s,num2str(i),txt);    
    delimiter = ',';
    startRow = 2;
    formatSpec = '%f%f%[^\n\r]';
    fileID = fopen(filename,'r');
    dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'EmptyValue' ,NaN,'HeaderLines' ,startRow-1, 'ReturnOnError', false);
    fclose(fileID);
    Days = dataArray{:, 1};
    StockPrice = dataArray{:, 2};
    hold on 
    plot(Days,StockPrice,'-*');
    str=strcat('Stock ',num2str(i));
    legend_mat=[legend_mat; str];
    end
    legend(legend_mat,'Location','SouthWest');
    xlabel('Time Period');
    ylabel('Stock Price');
    title('Moving Average of Stocks');
end