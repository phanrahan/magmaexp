% Model of Wallace Multiplier 
% Copyright 2007 Ron S Waters
% Commercial use prohibited without written authorization
%FINAL WORKING REVISION OF WALLACE REDUCTION CALCULATOR
andcnt=int16(0); %count of AND gates
cnt=int16(0);
facnt=0;%full adder count
hacnt=0;%half adder count
AA=[];
BB=[];
AX=(0); % X dimension of multiplier
AY=(0); % Y dimension of multiplier
BX=(0);
BY=(0);
xx=1;
stages=0;
% Input multiplier dimensions
AX = single(input('Input X dimension of multiplier: '));
AY=AX;
%AY = single(input('Input Y dimension of multiplier: '));
% define Partial Product Array
AA(AY,(2*AX))=zeros;
%Populate partial product array
b=AX;
for j=1:AY
    for k=b:(b+AX-1)
        
       AA(j,k+1)='A';
       
    end
    b=b-1;
end

sa=char(AA(:,:));
% Count number of AND gates in partial product array
for x=1:(2*AX)
    for y=1:AY
        
           c=int16(strcmp((sa(y,x)),'A'));
           andcnt=andcnt+c;
            
    end
end
disp(sa)
%------------------------
% Stage reduction
% Determine next stage array size
BX=(2*AX); %width of array
BY=fix(AY/3)*2+rem(AY,3);%depth of first stage
while BY>3
    BX=(2*AX); %width of array
    BY=fix(AY/3)*2+rem(AY,3);%depth of next stage
    BB(BY,BX)=zeros; % Define the array size for next level reduction
    sb=char(BB(:,:));
    % Calculate reduction
    aindx=1;
    for b=1:2:fix(AY/3)*2
  
        for c=BX:-1:1 
            if (sa(aindx,c)~=zeros && sa(aindx+1,c)==zeros && sa(aindx+2,c)==zeros) || (sa(aindx,c)==zeros && sa(aindx+1,c)==zeros && sa(aindx+2,c)~=zeros) || (sa(aindx,c)==zeros && sa(aindx+1,c)~=zeros && sa(aindx+2,c)==zeros)
                
                sb(b,c)='A'; 
                
                if c<AX && sb(b+1,c)==zeros
                    
                    sb(b,c)=zeros;
                    sb(b+1,c)='A';
                end
                                            
            elseif c>1 && ((sa(aindx,c)~=zeros && sa(aindx+1,c)~=zeros && sa(aindx+2,c)==zeros) || (sa(aindx,c)==zeros && sa(aindx+1,c)~=zeros && sa(aindx+2,c)~=zeros)|| (sa(aindx,c)~=zeros && sa(aindx+1,c)==zeros && sa(aindx+2,c)~=zeros))
                
                   sb(b,c)='H';
                   sb(b+1,c-1)='H';
                                 
            elseif c>1 && sa(aindx,c)~=zeros && sa(aindx+1,c)~=zeros && sa(aindx+2,c)~=zeros
                
                %check for triplet of partial products and if one, then
                %generate full adder
                sb(b,c)='F';
                sb(b+1,c-1)='F';
   
            end
        end
        
        aindx=aindx+3;
    
    end
%Generate bottom one or two rows in reduction stage if required, 

    for k=1:rem(AY,3)
        for m=1:2*AX
          if sa(AY-rem(AY,3)+k,m)=='F' || sa(AY-rem(AY,3)+k,m)=='H'
              
              sb(fix(AY/3)*2+k,m)='A';
              
          else 
              
              sb(fix(AY/3)*2+k,m)=sa(AY-rem(AY,3)+k,m);
              
          end
        end
    end

%Determine # full adders for stage
for x=1:BX
    for y=1:BY
        if sb(y,x)=='F'
            
            c=int16(strcmp((sb(y,x)),'F'));
            facnt=facnt+c;
            
        end
    
%Count number Half Adders

        if sb(y,x)=='H'
            
            c=int16(strcmp((sb(y,x)),'H'));
            hacnt=hacnt+c;
            
        end
    end
end
disp (sb)
stages=stages+1;
BY
AY=BY;
sa=[];
sa=sb(:,:);
xx=0;
end
%Analyze and calculate last reduction stage

while BY==3 
    sb(:,:)=zeros;
    aindx=1;
    b=1;
    for c=BX:-1:1 
            if (sa(aindx,c)~=zeros && sa(aindx+1,c)==zeros && sa(aindx+2,c)==zeros) || (sa(aindx,c)==zeros && sa(aindx+1,c)==zeros && sa(aindx+2,c)~=zeros) || (sa(aindx,c)==zeros && sa(aindx+1,c)~=zeros && sa(aindx+2,c)==zeros)
                
                sb(b,c)='A'; 
                      
            elseif c>1 && ((sa(aindx,c)~=zeros && sa(aindx+1,c)~=zeros && sa(aindx+2,c)==zeros) || (sa(aindx,c)==zeros && sa(aindx+1,c)~=zeros && sa(aindx+2,c)~=zeros)|| (sa(aindx,c)~=zeros && sa(aindx+1,c)==zeros && sa(aindx+2,c)~=zeros))
                
                   sb(b,c)='H';
                   sb(b+1,c-1)='H';
                                 
            elseif c>1 && sa(aindx,c)~=zeros && sa(aindx+1,c)~=zeros && sa(aindx+2,c)~=zeros
                
                %check for triplet of partial products and if one, then
                %generate full adder
                sb(b,c)='F';
                sb(b+1,c-1)='F';
   
            end
    end
    
%Determine # full adders for stage
    for x=1:BX
        for y=1:BY
            if sb(y,x)=='F'
                
                c=int16(strcmp((sb(y,x)),'F'));
                facnt=facnt+c;
                
            end
    
%Count number Half Adders
            if sb(y,x)=='H'
                
                c=int16(strcmp((sb(y,x)),'H'));
                hacnt=hacnt+c;
                
            end
        end
    end
    BY=2;
end
disp (sb)
%Display results
stages=stages+1;
facnt=facnt/2;
hacnt=hacnt/2;
andcnt
stages
facnt
hacnt
