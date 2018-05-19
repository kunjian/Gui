#ifndef TAKS_AFP_FACE_FACE_H
#define TAKS_AFP_FACE_FACE_H

#include <Gui/TaskView/TaskView.h>
#include <Gui/Selection.h>
#include <Gui/DocumentObserver.h>
#include <Gui/TaskView/TaskDialog.h>
#include <App/DocumentObject.h>

#include <Mod/Assembly/App/opendcm/core.hpp>
#include <Mod/Assembly/App/Solver/Solver.h>

#include <QComboBox>

#include "ViewProviderAFP.h"

namespace PartDesignGui
{
	class SoSwitch; //- 其作用目前还不清楚，需要继续确认，2018-05-12，xzj
	class Ui_TaskAFPFaceFace;

	class TaskAFPFaceFace : public Gui::TaskView::TaskBox, public Gui::SelectionObserver, public Gui::DocumentObserver
	{
		Q_OBJECT

	public:
		// 添加枚举变量，用于标识特征的状态，2018-05-12，xzj
		enum featureStatus {
			validFeature = 0,
			invalidShape,
			otherBody,
			otherPart,
			notInBody,
			AFPFace,
			afterTip
		};

		TaskAFPFaceFace(ViewProviderAFP* _vp, QWidget* _parent = 0); //增加特征状态参数，2018-05-12，xzj
		~TaskAFPFaceFace();

		App::DocumentObject* getFeature();

	protected Q_SLOTS:
		void onUpdate();
		void onSelectionChanged(const Gui::SelectionChanges& _msg);
		void onFaceSelection(const bool pressed = true);

		void onConstraintSelection(QComboBox* const _combBox);

	protected:
		const QString onAddSelection(const Gui::SelectionChanges& _msg, App::DocumentObject* _selObj, QString& _AFPText);
		void setLineEdit(QLineEdit* const _lnEdit, const QString _refText, const char* _subName, bool _onFaceSel, bool _faceSel);
		void exitSelectionMode();

		QString getFaceName(void) const;
		static QString getFaceReference(const QString& obj, const QString& sub);

		/** Notifies on undo */
		virtual void slotUndoDocument(const Gui::Document& _Doc);
		/** Notifies on document deletion */
		virtual void slotDeleteDocument(const Gui::Document& _Doc);

	private:
		Ui_TaskAFPFaceFace* m_ui;
		QWidget*            m_proxy;
		ViewProviderAFP*    m_view;

		std::string   m_documentName;
		QString       m_featureStr;

		const QString getFeatureStatusString(const featureStatus _st);
	};

	/// simulation dialog for the TaskView
	class TaskDlgAFPFaceFace : public Gui::TaskView::TaskDialog
	{
		Q_OBJECT

	public:
		TaskDlgAFPFaceFace(ViewProviderAFP* _vp);
		~TaskDlgAFPFaceFace();

	public:
		/// is called the TaskView when the dialog is opened
		virtual void open();
		/// is called by the framework if an button is clicked which has no accept or reject role
		virtual void clicked(int);
		/// is called by the framework if the dialog is accepted (Ok)
		virtual bool accept();
		/// is called by the framework if the dialog is rejected (Cancel)
		virtual bool reject();
		/// is called by the framework if the user presses the help button 
		virtual bool isAllowedAlterDocument(void) const
		{
			return false;
		}
		/// returns for Close and Help button 
		virtual QDialogButtonBox::StandardButtons getStandardButtons(void) const
		{
			return QDialogButtonBox::Ok | QDialogButtonBox::Cancel;
		}

	protected:
		TaskAFPFaceFace* m_facePick;
		ViewProviderAFP* m_view;
	};
}

#endif // TAKS_AFP_FACE_FACE_H
