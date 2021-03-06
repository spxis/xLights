#pragma once

/***************************************************************
 * This source files comes from the xLights project
 * https://www.xlights.org
 * https://github.com/smeighan/xLights
 * See the github commit history for a record of contributing
 * developers.
 * Copyright claimed based on commit dates recorded in Github
 * License: https://github.com/smeighan/xLights/blob/master/License.txt
 **************************************************************/

//(*Headers(EffectTreeDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
#include <wx/treectrl.h>
//*)
#include <wx/xml/xml.h>
#include <wx/filename.h>
#include <mutex>
#include <memory>

#include "effects/GIFImage.h"

class xLightsFrame;

class EffectTreeDialog : public wxDialog
{
    void ValidateWindow();
    void WriteEffect(wxFile& f, wxXmlNode* n);
    void WriteGroup(wxFile& f, wxXmlNode* n);

	public:

		EffectTreeDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~EffectTreeDialog();

		//(*Declarations(EffectTreeDialog)
		wxButton* ETButton1;
		wxButton* btAddGroup;
		wxButton* btApply;
		wxButton* btDelete;
		wxButton* btExport;
		wxButton* btImport;
		wxButton* btNewPreset;
		wxButton* btRename;
		wxButton* btUpdate;
		wxStaticBitmap* StaticBitmapGif;
		wxTextCtrl* TextCtrl1;
		wxTimer TimerGif;
		wxTreeCtrl* TreeCtrl1;
		//*)
        wxTreeItemId treeRootID;
        void InitItems(wxXmlNode *e);

	protected:

		//(*Identifiers(EffectTreeDialog)
		static const long ID_TREECTRL1;
		static const long ID_STATICBITMAP_GIF;
		static const long ID_BUTTON6;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON7;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON8;
		static const long ID_TEXTCTRL_SEARCH;
		static const long ID_BUTTON_SEARCH;
		static const long ID_TIMER_GIF;
		//*)

	private:

		//(*Handlers(EffectTreeDialog)
		void OnbtApplyClick(wxCommandEvent& event);
		void OnbtNewPresetClick(wxCommandEvent& event);
		void OnbtUpdateClick(wxCommandEvent& event);
		void OnbtRenameClick(wxCommandEvent& event);
		void OnbtDeleteClick(wxCommandEvent& event);
		void OnbtAddGroupClick(wxCommandEvent& event);
		void OnTreeCtrl1ItemActivated(wxTreeEvent& event);
		void OnButton_OKClick(wxCommandEvent& event);
		void OnTreeCtrl1BeginDrag(wxTreeEvent& event);
		void OnTreeCtrl1EndDrag(wxTreeEvent& event);
		void OnbtImportClick(wxCommandEvent& event);
		void OnbtExportClick(wxCommandEvent& event);
		void OnTreeCtrl1SelectionChanged(wxTreeEvent& event);
		void OnETButton1Click(wxCommandEvent& event);
		void OnTextCtrl1TextEnter(wxCommandEvent& event);
		void OnTimerGifTrigger(wxTimerEvent& event);
		//*)

		std::unique_ptr<wxBitmap> _blankGIFImage;
        std::unique_ptr<GIFImage> gifImage;
        int frameCount;
        xLightsFrame* xLightParent;
		wxXmlNode *XrgbEffectsNode;
        wxTreeItemId m_draggedItem;
        std::mutex preset_mutex;
        void AddTreeElementsRecursive(wxXmlNode *EffectsNode, wxTreeItemId curGroupID);
        wxXmlNode* CreateEffectGroupNode(wxString& name);
        void ApplyEffect(bool dblClick=false);
        void AddEffect(wxXmlNode* ele, wxTreeItemId curGroupID);
        void AddGroup(wxXmlNode* ele, wxTreeItemId curGroupID);
        void EffectsFileDirty();
        int GetOptimalPreviewSize();
    
        wxTreeItemId findTreeItem(wxTreeCtrl* pTreeCtrl, const wxTreeItemId& root, const wxTreeItemId& startID, const wxString& text, bool &startfound);

        void SearchForText();

		DECLARE_EVENT_TABLE()

        wxString ParseLayers(wxString name, wxString settings);
        wxString ParseDuration(wxString name, wxString settings);

		wxString generatePresetName(wxTreeItemId itemID);
        void GenerateGifImage(wxTreeItemId itemID, bool regenerate = false);
        void LoadGifImage(wxString const& path);
        void PlayGifImage();
        void StopGifImage();
        void DeleteGifImage(wxTreeItemId itemID);

    public:
        static bool PromptForName(wxWindow* parent, wxString *name, wxString prompt, wxString errorMsg); //static to allow re-use elsewhere -DJ
};

class MyTreeItemData : public wxTreeItemData
{
public:
    MyTreeItemData(wxXmlNode* desc, bool isGroup=false) {element=desc; _isGroup=isGroup; }

    wxXmlNode *GetElement() { return element; }
    bool IsGroup() { return _isGroup; }
private:
    wxXmlNode *element;
    bool _isGroup;
};
