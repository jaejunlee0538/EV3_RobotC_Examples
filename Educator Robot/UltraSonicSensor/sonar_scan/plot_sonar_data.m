file = fopen('sonar_scan_gyro_close_objects','r');
data = fread(file, [1, inf], 'float32');

xy = zeros(2, length(data));

%% in sensor frame
for i = 1:1:length(data)
    xy(:,i) = [data(i) 0];    
end

%% in body frame
for i = 1:1:length(data)
    xy(1,i) = xy(1,i) + 8.0; 
    xy(2,i) = xy(2,i) + 3.7;
end

% in world frame
for i = 1:1:length(data)
    angle =deg2rad(-i * 0.1);
    x = xy(1,i);
    y = xy(2,i);
    xy(1,i) = x*cos(angle) - y*sin(angle);
    xy(2,i) = x*sin(angle) + y*cos(angle);
%     xy(1,i) = xy(1,i)*cos(angle) - xy(2,i)*sin(angle);
%     xy(2,i) = xy(1,i)*sin(angle) + xy(2,i)*cos(angle);
end

%% plot
plot(xy(1,:), xy(2,:),'r.');
grid on;
xlim([-300 300]);
ylim([-300 300]);