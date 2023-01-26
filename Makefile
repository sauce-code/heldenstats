SRCS = datum.cpp Exception.cpp HeldenStatsDialog.cpp LineTransformer.cpp main.cpp moc_HeldenStatsDialog.cpp moc_MyHeldenStatsDialog.cpp MyHeldenStatsDialog.cpp Spieler.cpp StrFilter.cpp

EXEC = main

CPPFLAGS = -Iinclude

CFLAGS = -std=gnu11 #-O3 -Wall -pedantic
CXXFLAGS = -std=gnu++11 #-O3 -Wall -pedantic

DEPDIR = .dep
OBJDIR = obj
SRCDIR = src
OUTDIR = bin
$(shell mkdir -p $(DEPDIR) > /dev/null)
$(shell mkdir -p $(OBJDIR) > /dev/null)
$(shell mkdir -p $(SRCDIR) > /dev/null)
$(shell mkdir -p $(OUTDIR) > /dev/null)

OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td -I../../Qt/4.8.7/include/QtGui -I../../Qt/4.8.7/include/Qt3Support -I../../Qt/4.8.7/include/QtCore -L../../Qt/4.8.7/lib

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(OUTDIR)/$(EXEC)

clean:
	$(RM) $(DEPDIR)/*.d $(DEPDIR)/*.Td $(DEPDIR)/*~ $(OBJDIR)/*.o $(OBJDIR)/*~ $(OUTDIR)/*~ $(OUTDIR)/$(EXEC) $(SRCDIR)/*~

$(OBJDIR)/%.o : $(SRCDIR)/%.c
$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
$(OBJDIR)/%.o : $(SRCDIR)/%.cc $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o : $(SRCDIR)/%.cxx
$(OBJDIR)/%.o : $(SRCDIR)/%.cxx $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))