%%
% log data structure
% [time(ms) raw_rate(deg/s) filtered_rate(deg/s)]

%%
file = fopen('gyro_rate','r');
data = fread(file, [1, inf], 'float32');
t = data(1:3:end);
rate = data(2:3:end);
rate_filtered = data(3:3:end);

%% low pass filter simulation
rate_filtered2 = zeros(size(rate_filtered));

rate_filtered2(1) = rate(1);
alpha = 0.01;
for i=2:1:length(rate_filtered2)
    rate_filtered2(i) = (1-alpha)*rate_filtered2(i-1) + alpha*rate(i);
end

%% plot
plot(t, rate,'r','linewidth',2);
hold on;
plot(t, rate_filtered, 'b','linewidth',2);
plot(t, rate_filtered2, 'm', 'linewidth',1);
grid on;
legend('raw','filtered','filtered2');
