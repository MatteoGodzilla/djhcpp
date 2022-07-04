#include "TracklistingWindow.h"
using namespace tinyxml2;

void TracklistingWindow::ErrRequiredParameter(wxString paramenter){
    wxString message = "ERROR: Missing required parameter: ";
    message.append(paramenter);
    wxLogError(message);
    notEnoughParameters = true;
}

void TracklistingWindow::ErrInvalidParameter(wxString paramenter, wxString type){
    wxString message = "ERROR: the parameter provided is of the wrong type: ";
    message.append(paramenter);
    message.append(".\nIt should be of type: ");
    message.append(type);
    wxLogError(message);
    invalidFormatParameters = true;
}

TracklistingWindow::TracklistingWindow(wxWindow* parent) : TracklistingGen(parent){}

void TracklistingWindow::GenTracklisting(wxCommandEvent& event){
    //set up
    XMLDocument doc;
    doc.InsertEndChild(doc.NewElement("TrackListing"));
    std::map<wxString,wxString> csv;

    XMLElement* track = doc.NewElement("Track");
    track->SetAttribute("ingame",true);
    track->SetAttribute("ondisc",true);
    track->SetAttribute("selectableinfem","yes");

    notEnoughParameters = false;
    invalidFormatParameters = false;

    //general informations

    if(!m_textID->IsEmpty()) {
        XMLElement* elm = doc.NewElement("IDTag");
        elm->InsertNewText(m_textID->GetValue());
        track->InsertEndChild(elm);
    } else {
        ErrRequiredParameter("ID");
    }

    if(!m_textBPM->IsEmpty()) {
        double bpm;
        bool success = m_textBPM->GetValue().ToDouble(&bpm);
        if(success){
            XMLElement* elm = doc.NewElement("BPM");
            elm->SetText(bpm);
            track->InsertEndChild(elm);
        } else {
            ErrInvalidParameter("BPM","number");
        }
    } else {
        ErrRequiredParameter("BPM");
    }

    //TODO: replace this with ids to add to the CSV

    if(!m_textArtist1->IsEmpty()) {
        XMLElement* elm = doc.NewElement("MixArtist");
        wxString val = m_textArtist1->GetValue();
        wxString id = GenerateID(val);
        csv.insert_or_assign(id,val);

        elm->InsertNewText(id);
        track->InsertEndChild(elm);
    } else {
        ErrRequiredParameter("Artist 1");
    }

    if(!m_textSong1->IsEmpty()) {
        XMLElement* elm = doc.NewElement("MixSong");
        wxString val = m_textSong1->GetValue();
        wxString id = GenerateID(val);
        csv.insert_or_assign(id,val);

        elm->InsertNewText(id);
        track->InsertEndChild(elm);
    } else {
        ErrRequiredParameter("Song 1");
    }

    if(!m_textArtist2->IsEmpty()) {
        XMLElement* elm = doc.NewElement("MixArtist");
        wxString val = m_textArtist2->GetValue();
        wxString id = GenerateID(val);
        csv.insert_or_assign(id,val);

        elm->InsertNewText(id);
        track->InsertEndChild(elm);
    }

    if(!m_textSong2->IsEmpty()) {
        XMLElement* elm = doc.NewElement("MixSong");
        wxString val = m_textSong2->GetValue();
        wxString id = GenerateID(val);
        csv.insert_or_assign(id,val);

        elm->InsertNewText(id);
        track->InsertEndChild(elm);
    }

    if(!m_textMixedBy->IsEmpty()) {
        XMLElement* elm = doc.NewElement("MixHeadlineDJName");
        wxString val = m_textMixedBy->GetValue();
        wxString id = GenerateID(val);
        csv.insert_or_assign(id,val);

        elm->InsertNewText(id);
        track->InsertEndChild(elm);
    }

    if(!m_textMixerPresents->IsEmpty()) {
        XMLElement* elm = doc.NewElement("MixHeadline");
        wxString val = m_textMixerPresents->GetValue();
        wxString id = GenerateID(val);
        csv.insert_or_assign(id,val);

        elm->InsertNewText(id);
        track->InsertEndChild(elm);
    }

    //difficulty informations
    if(!m_textDiffGeneral->IsEmpty()){
        //float bpm = m_textBPM->GetValue().ToDouble
        long diff;
        bool success = m_textDiffGeneral->GetValue().ToLong(&diff);
        if(success){
            XMLElement* elm = doc.NewElement("TrackComplexity");
            elm->SetText((int64_t)diff);
            track->InsertEndChild(elm);
        } else {
            ErrInvalidParameter("Difficulty General","number");
        }
    } else {
        ErrRequiredParameter("Difficulty General");
    }

    if(!m_textDiffTap->IsEmpty()){
        long diff;
        bool success = m_textDiffTap->GetValue().ToLong(&diff);
        if(success){
            XMLElement* elm = doc.NewElement("TapComplexity");
            elm->SetText((int64_t)diff);
            track->InsertEndChild(elm);
        } else {
            ErrInvalidParameter("Difficulty Tap","number");
        }
    } else {
        ErrRequiredParameter("Difficulty Tap");
    }
    
    if(!m_textDiffScratch->IsEmpty()){
        long diff;
        bool success = m_textDiffScratch->GetValue().ToLong(&diff);
        if(success){
            XMLElement* elm = doc.NewElement("ScratchComplexity");
            elm->SetText((int64_t)diff);
            track->InsertEndChild(elm);
        } else {
            ErrInvalidParameter("Difficulty Scratch","number");
        }
    } else {
        ErrRequiredParameter("Difficulty Scratch");
    }

    if(!m_textDiffCrossfade->IsEmpty()){
        long diff;
        bool success = m_textDiffCrossfade->GetValue().ToLong(&diff);
        if(success){
            XMLElement* elm = doc.NewElement("CrossfadeComplexity");
            elm->SetText((int64_t)diff);
            track->InsertEndChild(elm);
        } else {
            ErrInvalidParameter("Difficulty Crossfade","number");
        }
    } else {
        ErrRequiredParameter("Difficulty Crossfade");
    }

    //extras
    if(!m_textBPM->IsEmpty()){
        if(!m_textSpeed->IsEmpty()){
            double speed;
            double bpm;
            bool success = m_textSpeed->GetValue().ToDouble(&speed);
            success = success && m_textBPM->GetValue().ToDouble(&bpm);
            if(success){
                //round down to 2 decimal digits
                double multiplier = speed / bpm;
                multiplier = round(multiplier * 100) / 100;
                for(int i = 0; i < 5; i++){
                    XMLElement* elm = doc.NewElement("DeckSpeedMultiplier");
                    elm->SetAttribute("Difficulty",i);
                    //yes i absolutely know that this suffers from buffer overflows
                    char buffer[100];
                    sprintf(buffer,"%.2f",multiplier);
                    elm->SetText(buffer);
                    track->InsertEndChild(elm);
                }
            } else {
                ErrInvalidParameter("DeckSpeed","number");
            }
        } else {
            //write galvanize defaults
            double bpm;
            bool success = m_textBPM->GetValue().ToDouble(&bpm);
            if(success){
                double speeds[5] = {240.0,240.0,250.0,300.0,400.0}; 
                //calculate mults
                for(int i = 0; i < 5; i++){
                    //round down to 2 decimal points
                    double multiplier = speeds[i] / bpm;
                    multiplier = round(multiplier * 100.0) / 100.0;
                    XMLElement* elm = doc.NewElement("DeckSpeedMultiplier");
                    elm->SetAttribute("Difficulty",i);
                    //yes i absolutely know that this suffers from buffer overflows
                    char buffer[100];
                    sprintf(buffer,"%.2f",multiplier);
                    elm->SetText(buffer);
                    track->InsertEndChild(elm);
                }
            }
        }
    }

    if(!m_textDuration->IsEmpty()){
        long duration;
        bool success = m_textDuration->GetValue().ToLong(&duration);
        if(success){
            XMLElement* elm = doc.NewElement("TrackDuration");
            elm->SetText((int64_t)duration);
            track->InsertEndChild(elm);
        } else {
            ErrInvalidParameter("Track Duration","number");
        }
    }

    if(m_checkBoxIsVocal->IsChecked()){
        XMLElement* elm = doc.NewElement("HasVocalMarkup");
        elm->SetText("1");
        track->InsertEndChild(elm);
    }

    if(m_checkBoxIsMenuMusic->IsChecked()){
        XMLElement* elm = doc.NewElement("IsMenuMusic");
        elm->SetText("1");
        track->InsertEndChild(elm);
    }

    if(notEnoughParameters || invalidFormatParameters){
        return;
    }

    //output to user
    doc.RootElement()->InsertEndChild(track);
    xmlOutput->Clear();
    XMLPrinter printer;
    doc.Print(&printer);
    xmlOutput->AppendText(printer.CStr());

    csvOutput->Clear();
    for(auto& pair : csv){
        wxString line;
        line.append(pair.first);
        line.append(",");
        line.append(pair.second);
        line.append("\n");
        csvOutput->AppendText(line);
    }
}

void TracklistingWindow::GenBaseFolder(wxCommandEvent& event){
    wxLogWarning("Not done yet, sorry :(");
}

wxString TracklistingWindow::GenerateID(wxString source){
    wxString res = "STR_";
    res.append(source.Upper());
    return res;
}