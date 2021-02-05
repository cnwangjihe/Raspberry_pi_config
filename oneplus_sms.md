Oneplus修改信息:
1.Android自身储存:
	/data/data/com.android.providers.telephony/databases/mmssms.db
	sqlite数据库，修改sms(date,date_sent,body)
2.一加信息应用：
	里面的id默认指messages(id)，messages中的content://sms/$id$,$id$指向mmssms.db中的sms(id)
	若是某个会话的最新消息，请先修改conversations(snippet_text,sort_timestamp)、conversation_list_view(snippet_text,sort_timestamp)、parts(text,timestamp)
	修改messages(sent_timestamp,received_timestamp)
