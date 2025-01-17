function obj=montage(obj,pathnames)
% get the names of the images
global self;
global ogh;
global objects;
filenames=obj.state.display.filenames;
if (nargin==1)
    pathnames=obj.state.display.pathnames;
end
pathname=obj.state.pathname;

figure;

totaly=ceil(max(size(pathnames))/2);

for i=1:max(size(pathnames))
    [path,name,ext] = fileparts([char(pathnames(i))]);
    [name,status]=strtok(name,'_');
    self=struct(obj);
    ogh=self.gh;
    if (strcmp(ext,'.spi'))      
        try
            self=[];
            ogh=[];
            
            warning off MATLAB:MKDIR:DirectoryExists;
            mkdir(path, [name 'ziptemp']);
            h = waitbar(0,'Unzipping Spi File...', 'Name', 'Unzipping Spi File', 'Pointer', 'watch');
            waitbar(0,h, ['Unzipping Spi File...']);
            if exist([path '\' name 'ziptemp'],'dir')
                tiffile=dir([path '\' name 'ziptemp\*.tif']);
                filtif=dir([path '\' name 'ziptemp\*.tif']);
                datfile=dir([path '\' name 'ziptemp\*.dat']);
                if ~((size(tiffile,1)>=2) & (size(filtif,1)>=1) & (size(datfile,1)>=1))
                    % infounzip([path '\' name ext],[path '\' name 'ziptemp']);
                    [s,w]=system(['unzip -u ' path '\' name status ext ' -d ' path '\' name 'ziptemp']);
                    if (s~=0)
                        disp('Could not unzip data');
                        close(h);
                        return;
                    end
                end
            else
                %  infounzip([path '\' name ext],[path '\' name 'ziptemp']);
                [s,w]=system(['unzip -u ' path '\' name status ext ' -d ' path '\' name 'ziptemp']);
                if (s~=0)
                    disp('Could not unzip data');
                    close(h);
                    return;
                end
            end
            try
                cd ([path '\' name 'ziptemp\ziptemp']);
                copyfile('*.*','..');
            catch
                
            end
            waitbar(1,h, 'Done');
            close(h);
            
            
            cd (path);               
            
            datfile=dir([path '\' name 'ziptemp\*.dat']);
            load('-mat',[path '\' name 'ziptemp\' datfile(1).name]);
            
            tiffile=dir([path '\' name 'ziptemp\*.tif']);
            try
                rawArray=opentif([path '\' name 'ziptemp\' tiffile(1).name]);  % get the filtered image
            catch
                disp('warning: no rawImage found');
            end    
            self.data.imageArray=rawArray;
            rawArray=[];
            subplot(totaly,2,i);
            if isfield(self.state.display,'colormap')
                colormap(self.state.display.colormap);
            end
            if (strcmp(status,'_edited'))
                self.state.display.highpixel=300;%double(max([self.data.dendrites.meanback]))*3;
            else
                self.state.display.highpixel=200;
            end
            
            if isfield(self.data,'imageArray')
                h=imagesc(collapse(self.data.imageArray(:,:,:),'XY'),[self.state.display.lowpixel self.state.display.highpixel]);
                %h=imagesc(collapse(self.data.imageArray(:,:,self.state.ROI.minz:self.state.ROI.maxz),'XY'),[self.state.display.lowpixel self.state.display.highpixel]);
            else
                cla;
            end
            if isfield(self.data,'ROI') & length(self.data.ROI)
                xlabel(['meanimageback ' num2str( self.data.imagemedian) ' ROI ' num2str(self.data.ROI.meanintensity)]);
            else
                xlabel(['meanimageback ' num2str( self.data.imagemedian)]);
            end
            hold on;
            %             for i=1:size(self.data.dendrites,2)
            %                 h=plot(double(self.data.dendrites(i).voxel(2,:)),double(self.data.dendrites(i).voxel(1,:)));
            %                 set(h,'LineWidth',2);
            %                 set(h,'ButtonDownFcn','spineanalysisimageGUI(''projectionimageaxes_ButtonDownFcn'',gcbo,[],guidata(gcbo))');
            %                 set(h,'color',hsv2rgb([i/size(self.data.dendrites,2) 0.8 0.8]),'Tag',[self.state.rawImageName '_axonnumber#' num2str(i)]);
            %                 h=text(double(self.data.dendrites(i).voxel(2,floor(size(self.data.dendrites(i).voxel,1)/2))),double(self.data.dendrites(i).voxel(1,floor(size(self.data.dendrites(i).voxel,1)/2))),char(64+i));
            %                 set(h,'Color',[0 1 0]);
            %             end
            
            if 1 % display all boutons?
                
                for i=1:size(self.data.spines,2)
                    if ((self.data.spines(i).edittype~=3) & ((self.data.spines(i).edittype~=1) | (self.state.display.displayrejectedspine)))
                        colorvec=[1 0 0];
                        if self.state.display.displayentirespine==1 
                            h=plot(double(self.data.spines(i).voxel(2,3:end)),double(self.data.spines(i).voxel(1,3:end)),'.');
                            if self.data.spines(i).edittype==1
                                colorvec=[0.5 0.5 0.5];
                            else
                                colorvec=[0.5 0.5 0.5];
                            end
                        else
                            if (self.data.spines(i).label>0)
                                if sum(self.data.spines(i).voxel(1:2,1)-self.data.spines(i).voxel(1:2,2)==[0 0]')==2
                                    h=plot(self.data.spines(i).voxel(2,1),self.data.spines(i).voxel(1,1),'.');
                                    set(h,'MarkerSize',4);
                                    set(h,'Color',[1 0 0],'Tag',[self.state.rawImageName '_spinenumber#' num2str(self.data.spines(i).label) '_axonnumber#' num2str(self.data.spines(i).den_ind)]);
                                else                    
                                    h=plot(self.data.spines(i).voxel(2,1:2),self.data.spines(i).voxel(1,1:2));
                                    set(h,'LineWidth',3);
                                    set(h,'Color',[0.5 0.5 0.5]);
                                end
                                if self.data.spines(i).edittype==1
                                    colorvec=[0 1 0];
                                elseif self.data.spines(i).edittype==2
                                    colorvec=[1 1 0]; 
                                else
                                    colorvec=[1 0 0];
                                end
                                set(h,'Color',colorvec);
                            end
                        end 
                        
                        if (self.data.spines(i).label>0)
                            if self.data.spines(i).len<0.5    % right on the axon?
                                ind1=min(self.data.spines(i).dendis+10,size(self.data.dendrites(self.data.spines(i).den_ind).voxel,2));
                                ind2=max(self.data.spines(i).dendis-10,1);
                                dx=mean(self.data.dendrites(self.data.spines(i).den_ind).dx(ind2:ind1));
                                dy=mean(self.data.dendrites(self.data.spines(i).den_ind).dy(ind2:ind1));
                                h=text(double(self.data.spines(i).voxel(2,1))-dy*15-5,double(self.data.spines(i).voxel(1,1))+dx*20-8,int2str(self.data.spines(i).label));
                                set(h,'Color',[1 0 0]);    
                            else
                                h=text(double(self.data.spines(i).voxel(2,2))*2.5-double(self.data.spines(i).voxel(2,1))*1.5-3,double(self.data.spines(i).voxel(1,2))*2.5-double(self.data.spines(i).voxel(1,1))*1.5-3,int2str(self.data.spines(i).label));
                                set(h,'Color',[0 1 0]);    
                            end
                            
                        end
                    end
                end
            else    % display only terminal boutons
                 for i=1:size(self.data.spines,2)
                    if ((self.data.spines(i).edittype~=3) & ((self.data.spines(i).edittype~=1) | (self.state.display.displayrejectedspine)))
                        colorvec=[1 0 0];
                        if self.state.display.displayentirespine==1 
                            h=plot(double(self.data.spines(i).voxel(2,3:end)),double(self.data.spines(i).voxel(1,3:end)),'.');
                            if self.data.spines(i).edittype==1
                                colorvec=[0.5 0.5 0.5];
                            else
                                colorvec=[0.5 0.5 0.5];
                            end
                        else
                            if (self.data.spines(i).label>0)
                                if sum(self.data.spines(i).voxel(1:2,1)-self.data.spines(i).voxel(1:2,2)==[0 0]')==2
                                else                    
                                    h=plot(self.data.spines(i).voxel(2,1:2),self.data.spines(i).voxel(1,1:2));
                                    set(h,'LineWidth',3);
                                    set(h,'Color',[0.5 0.5 0.5]);
                                    
                                 if self.data.spines(i).edittype==1
                                    colorvec=[0 1 0];
                                elseif self.data.spines(i).edittype==2
                                    colorvec=[1 1 0]; 
                                else
                                    colorvec=[1 0 0];
                                end
                                set(h,'Color',colorvec);
                            end
                            end
                        end 
                        
                        if (self.data.spines(i).label>0)
                            if self.data.spines(i).len<0.05    % right on the axon?
                               
                            else
                                direction=[double(self.data.spines(i).voxel(2,2))-double(self.data.spines(i).voxel(2,1)) double(self.data.spines(i).voxel(1,2))-double(self.data.spines(i).voxel(1,1))];
                                direction=direction/sqrt(sum(direction.*direction));
                                co=[double(self.data.spines(i).voxel(2,2)) double(self.data.spines(i).voxel(1,2))]+direction*20-[3 3];
                                
                                h=text(co(1),co(2),int2str(self.data.spines(i).label));
            
                                set(h,'Color',[0 1 0]);    
                            end
                            
                        end
                    end
                end
            end

            self=[];    
        catch
            disp(['error processing:' name]);
            disp(lasterr);
        end
    else
         
                imageArray=opentif([char(pathnames(i))]);  % get the filtered image
               subplot(totaly,2,i);
                h=imagesc(collapse(imageArray,'XY'),[0 200]);          
    end   
end
